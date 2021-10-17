//
// Created by daniel on 24.09.21.
//

#pragma once
#include "utils.hpp"
#include "../ui/controls/listbox.hpp"
#include "../player.hpp"
#include "../items/items.hpp"

namespace savegame {
	struct Item {
		listbox_item::INVENTORY_ITEM type;
		uint8_t amount;
	};

	struct GameData {
		bool show_fps;
		map::MapSections map_section;
		Point camera_position;
		Player::MovementDirection player_direction;
		std::array<Item, listbox_item::INVENTORY_COUNTER> items;
		std::array<bool, StargateAddresses::COUNTER> gate_states;
	};

	Player *create();
	void save(uint8_t save_id);
	Player *load(uint8_t save_id);
}
