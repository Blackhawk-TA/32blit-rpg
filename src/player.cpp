//
// Created by daniel on 21.08.21.
//

#include <assets.hpp>
#include "player.hpp"
#include "engine/camera.hpp"
#include "engine/map.hpp"
#include "building.hpp"
#include "engine/transition.hpp"
#include "engine/flags.hpp"
#include "handlers/stargate_handler.hpp"
#include "game_objects/stargate.hpp"

bool Player::is_moving = false;
Timer *Player::animation_timer;
uint16_t Player::sprite_index = 0;
std::array<uint16_t, Player::ANIMATION_SPRITE_COUNT> Player::animation_sprites;

//Camera is scaled by the factor of 100 to prevent rounding issues
Player::Player() {
	Player::position = get_screen_tiles() / 2;
	Player::characters = Surface::load(asset_characters);
	Player::spritesheet_size = get_spritesheet_size(Player::characters->bounds);

	//Set player animation tiles
	Player::current_direction = MovementDirection::DOWN;
	Player::animation_sprites = movement_sprites.at(Player::current_direction);
	Player::sprite_index = animation_sprites[0];

	animation_timer = new Timer();
	animation_timer->init(animate, 175, -1);
}

void Player::animate(Timer &timer) {
	if ((is_moving || camera::is_moving()) && !transition::in_progress()) {
		sprite_index = animation_sprites[(sprite_index + 1) % ANIMATION_SPRITE_COUNT];
	} else {
		sprite_index = animation_sprites[0];
		animation_timer->stop();
	}
}

void Player::stop_movement() {
	is_moving = false;
}

void Player::move(MovementDirection direction) {
	//Do not move when a transition is in progress
	if (transition::in_progress()) {
		return;
	}

	Point movement = movements.at(direction);
	is_moving = true;

	//Do not trigger a movement while another one is in progress
	if (camera::is_moving()) {
		return;
	}

	//Start animation timer if not already running
	if (!animation_timer->is_running()) {
		animation_timer->start();
	}

	//Set player sprite direction
	set_direction(direction);

	//Move player according to tile flag of next position
	Point next_position = camera::get_world_position() + position + movement;
	uint8_t building_id;

	if (stargate_handler::check_collisions(next_position)) {
		is_moving = false;
		return;
	}

	//Check if teleport destination is available
	Stargate *destination_gate = stargate_handler::get_destination_gate(next_position);
	if (destination_gate != nullptr) {
		//Trigger teleportation
		transition::start([destination_gate, this] {
			gate_teleport(destination_gate);
		});
		is_moving = false;
		return;
	}

	//Update the stargate states when a player comes near them
	stargate_handler::update_states(next_position);

	switch (map::get_flag(next_position)) {
		case flags::TileFlags::WALKABLE:
			camera::move(movement);
			break;
		case flags::TileFlags::DOOR:
			building_id = building::get_id(next_position, map::get_section());

			//No building found, stop movement
			if (building_id == 255) {
				is_moving = false;
				return;
			}

			//Teleport to position on different tile map
			transition::start([building_id, next_position] {
				building_teleport(building_id, next_position);
			});
			camera::move(movement);
			break;
		default:
			is_moving = false;
	}
}

void Player::set_direction(MovementDirection direction) {
	if (current_direction != direction) {
		animation_sprites = movement_sprites.at(direction);
		current_direction = direction;
		sprite_index = animation_sprites[0]; //Set sprite manually to avoid timer delay on player turn
	}
}

void Player::draw() {
	screen.blit(
		characters,
		Rect((sprite_index % spritesheet_size.w) * TILE_SIZE, (sprite_index / spritesheet_size.h) * TILE_SIZE,
		     TILE_SIZE, TILE_SIZE),
		world_to_screen(position),
		SpriteTransform::NONE
	);
}

/**
 * Teleports the player to the interior/exterior of the building and swaps the tile maps
 * @param building_id The id of the building
 * @param next_position The position where the player will walk within the next move
 */
void Player::building_teleport(uint8_t building_id, Point next_position) {
	Point destination;

	if (next_position == building::connections[building_id].exterior) {
		map::load_section(map::MapSections::INTERIOR);
		destination = building::connections[building_id].interior;
	} else if (next_position == building::connections[building_id].interior) {
		map::load_section(map::MapSections::GRASSLAND);
		Point door_offset = Point(0, 1); //Teleport player in front of the door instead of directly on it
		destination = building::connections[building_id].exterior + door_offset;
	}

	camera::set_position(destination);
}

/**
 * Teleports a player to the given gate and sets the movement direction to facing downwards
 * @param destination_gate The gate to which the player is teleported
 */
void Player::gate_teleport(Stargate *destination_gate) {
	Point teleport_destination = destination_gate->get_entry_point();
	map::MapSections destination_map_section = destination_gate->get_map_section();
	if (map::get_section() != destination_map_section) {
		map::load_section(destination_map_section);
	}

	camera::set_position(teleport_destination);
	set_direction(MovementDirection::DOWN);
	stargate_handler::update_states(teleport_destination);
}
