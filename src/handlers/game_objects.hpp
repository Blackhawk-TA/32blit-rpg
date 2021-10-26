//
// Created by D069765 on 26.10.2021.
//

#pragma once
#include "../game_objects/game_object_interface.hpp"

//TODO think about integrating stargate into a gameobject, might not make sense since a gate is special due to the objects being linked
namespace game_objects {
	/**
	 * Creates the objects using their factory function
	 */
	void init();

	/**
	 * Load object states from savegame
	 */
	void load();

	/**
	 * Save object states to savegame //TODO should return savable structure and is called by savegame utils
	 */
	void save();

	/**
	 * Draws all game objects
	 */
	void draw();

	/**
	 * Check if a game object collides with the player's next position
	 * @param next_position
	 * @return
	 */
	bool check_collisions(Point next_position);

	/**
	 * Checks if there was an interaction with a game object and trigger interaction
	 * @return True, if interaction successful, else false
	 */
	bool interact();

	/**
	 * Updates the states of the objects when a player moves closer to it
	 * @param next_position The next position of the player
	 */
	void update_states(Point next_position);
}
