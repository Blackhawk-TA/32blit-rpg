//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

class Salesman : public Character {
private:
	const uint16_t TILE_ID = 0;
	const uint8_t BAR_HEIGHT = 1;

	void set_state(uint8_t new_state) override;

public:
	explicit Salesman(map::MapSections map_section, Point position);
	~Salesman() override = default;
	void update(uint32_t time) override;
	void update_state(Point next_position) override;
	ObjectType get_type() override;
	bool player_interact() override;
};
