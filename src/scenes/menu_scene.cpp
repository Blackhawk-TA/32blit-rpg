//
// Created by daniel on 17.10.21.
//

#include "menu_scene.hpp"
#include "../game.hpp"
#include "../items/items.hpp"
#include "../utils/saves/options.hpp"

MenuScene::MenuScene() {
	last_buttons = 0;
	changed = 0;

	options::OptionsData options_data = options::load();
	saves_count = options_data.save_count;

	create_list_entries();

	listbox = new Listbox(Rect(0, 0, 5, 6), saves, false);
}

MenuScene::~MenuScene() {
	delete listbox;
	listbox = nullptr;
}

void MenuScene::create_list_entries() {
	for (uint8_t i = 0u; i < saves_count; i++) {
		saves.emplace_back(listbox_item::create_menu_item(listbox_item::MENU_ITEM::LOAD_SAVE, i + 1));
	}

	if (saves_count < options::MAX_SAVES) {
		saves.emplace_back(listbox_item::create_menu_item(listbox_item::MENU_ITEM::NEW_SAVE, saves_count + 1));
	}

	saves.emplace_back(listbox_item::create_menu_item(listbox_item::MENU_ITEM::MENU_OPTIONS));
}

void MenuScene::render(uint32_t time) {
	screen.pen = Pen(0, 0, 0, 255);
	screen.rectangle(Rect(0, 0, 320, 240));

	listbox->draw();
}

void MenuScene::update(uint32_t time) {
	//Handle button inputs
	changed = buttons ^ last_buttons;

	if (buttons & changed & Button::DPAD_UP) {
		listbox->cursor_up();
	} else if (buttons & changed & Button::DPAD_DOWN) {
		listbox->cursor_down();
	} else if (buttons & changed & Button::A) {
		listbox->cursor_press();
	}

	last_buttons = buttons;
}
