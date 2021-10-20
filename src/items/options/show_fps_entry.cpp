//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../utils/saves/options.hpp"

Listbox::Item listbox_item::create_show_fps_entry() {
	return Listbox::Item{
		"SHOW FPS",
		"Press A to toggle the fps counter.",
		"Toggled fps counter.",
		"",
		false,
		0,
		[] {
			options::show_fps = !options::show_fps;
			return Listbox::Tooltip::SUCCESS;
		}
	};
}
