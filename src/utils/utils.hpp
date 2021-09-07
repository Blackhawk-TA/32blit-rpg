//
// Created by daniel on 27.02.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

//Sprite and map constants. All TileMaps require to have the same size.
constexpr uint8_t TILE_SIZE = 16;
//TODO calculate in map class and create getter
constexpr uint8_t LEVEL_WIDTH = 128;
constexpr uint8_t LEVEL_HEIGHT = 128;
constexpr uint16_t LEVEL_SIZE = LEVEL_WIDTH * LEVEL_HEIGHT;

Vec2 screen_to_world(const Vec2 &p);
Point screen_to_world(const Point &p);

Point world_to_screen(const Point &p);
Point world_to_screen(const float &x, const float &y);

Point get_sprite_sheet_size(Size bounds);
Point get_screen_tiles();
