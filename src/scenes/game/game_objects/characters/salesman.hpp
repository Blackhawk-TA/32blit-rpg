//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

namespace game {
	class Salesman : public Character {
	private:
		const uint16_t TILE_ID = 68;
		const uint8_t BAR_HEIGHT = 1;

	public:
		explicit Salesman(map::MapSection map_section, Point position);
		~Salesman() override = default;
		bool player_interact() override;
	};
}
