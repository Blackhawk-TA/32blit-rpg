//
// Created by daniel on 07.11.21.
//

#include "../items.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"
#include "../../scenes/game/game_objects/handler/player_handler.hpp"

Listbox::Item items::create_shop_spear(uint8_t type_id) {
	uint8_t price = 175;
	return Listbox::Item{
		type_id,
		"SPEAR",
		"Buy a spear for " + std::to_string(price) + " gold. It can be used during fights to defend yourself.",
		"You bought a spear for " + std::to_string(price) + " gold",
		"You can't buy this now.",
		false,
		0,
		[price] {
			Listbox::Item item = items::create_gear_item(GEAR_SPEAR);
			if (game::sidemenu::has_item(game::sidemenu::MenuType::GEAR, item)) {
				return Listbox::Tooltip::FAILURE;
			} else {
				if (game::player_handler::remove_gold(price)
				&& game::sidemenu::add_item(game::sidemenu::GEAR, item)) {
					return Listbox::Tooltip::SUCCESS;
				} else {
					return Listbox::Tooltip::FAILURE;
				}
			}
		}
	};
}
