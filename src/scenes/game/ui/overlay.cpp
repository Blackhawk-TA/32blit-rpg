//
// Created by Daniel Peters on 12.04.21.
//

#include "overlay.hpp"
#include "../game_objects/handler/player_handler.hpp"

using namespace blit;

namespace game::overlay {
	void draw_statusbar() {
		const uint8_t BAR_HEIGHT = 10;
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(0, 0, screen.bounds.w, BAR_HEIGHT));

		screen.pen = Pen(0, 0, 0, 255);
		std::string health_string = "Health: " + std::to_string(player_handler::get_health()) +
			" | Gold: " + std::to_string(player_handler::get_gold()) +
			" | Level: " + std::to_string(player_handler::get_level());
		screen.text(health_string, minimal_font, Rect(3, 1, 10, 10), false, TextAlign::left);

		screen.pen = Pen(155, 155, 155, 200);
		screen.rectangle(Rect(0, BAR_HEIGHT, screen.bounds.w, 2));

		screen.pen = Pen(0, 255, 0, 200);
		screen.rectangle(Rect(0, BAR_HEIGHT, int(float(player_handler::get_xp()) / float(
			player_handler::get_next_level_max_xp()) * float(screen.bounds.w)), 2));
	}
}
