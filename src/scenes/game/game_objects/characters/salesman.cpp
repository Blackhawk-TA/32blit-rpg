//
// Created by daniel on 24.11.21.
//

#include "salesman.hpp"
#include "../../../../engine/camera.hpp"

namespace game {
	Salesman::Salesman(map::MapSections map_section, Point position) : Character(map_section, position, true, false) {
		tile_id = TILE_ID;
		movement_sprites = {
			{UP,    {116, 117, 118, 119}},
			{DOWN,  {68,  69,  70,  71}},
			{LEFT,  {84,  85,  86,  87}},
			{RIGHT, {100, 101, 102, 103}}
		};
	}

	bool Salesman::player_interact() {
		if (player_usable && camera::get_player_position() == position + Point(0, size.h + BAR_HEIGHT)) {
			textbox = new Textbox("Hello! Normally I would sell you carrot seeds but they are all gone.");
			return true;
		}

		return false;
	}

	void Salesman::update_state(Point next_position) {}

	void Salesman::set_state(uint8_t new_state) {}

	void Salesman::update(uint32_t time) {}
}
