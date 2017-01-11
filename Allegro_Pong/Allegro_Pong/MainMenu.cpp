#include "GameState.h"

enum MouseActions {
	MouseB1Down, MouseB1Up 
};


//MainMenu class functions

MainMenu::MainMenu() {

	play_button.x = SCREEN_WIDTH / 2;
	play_button.y = SCREEN_HEIGHT / 2 -50;
	play_button.height = 50;
	play_button.width = 200;
	play_button.state = NOT_PRESSED;

	exit_button.x = SCREEN_WIDTH / 2;
	exit_button.y = SCREEN_HEIGHT / 2 + 50;
	exit_button.height = 50;
	exit_button.width = 200;
	exit_button.state = NOT_PRESSED;

	font = al_load_ttf_font("arial.ttf", 30, 0);

	mouse_event_queue = al_create_event_queue();
	al_register_event_source(mouse_event_queue, al_get_mouse_event_source());


	for (int i = 0; i <= 2; i++) {
		actions[i] = false;
	}

}

MainMenu::~MainMenu() {

	al_destroy_font(font);

	al_destroy_event_queue(mouse_event_queue);
}

void MainMenu::handle_events() {

	ALLEGRO_EVENT mouse_event;


	while (al_is_event_queue_empty(mouse_event_queue) == false) {

		al_get_next_event(mouse_event_queue, &mouse_event);

		switch (mouse_event.type) {
			case ALLEGRO_EVENT_MOUSE_AXES:
				mouse_x = mouse_event.mouse.x;
				mouse_y = mouse_event.mouse.y;
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				
				switch (mouse_event.mouse.button) {

					case 1:
						actions[MouseB1Up] = false;
						actions[MouseB1Down] = true;
						break;
					default:
						break;
				}
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				switch (mouse_event.mouse.button) {

				case 1:
					actions[MouseB1Up] = true;
					actions[MouseB1Down] = false;
					break;
				default:
					break;
				}
				break;

			default:
				break;
		}

			
	}



}

void MainMenu::logic() {



}

void MainMenu::render() {

	al_draw_filled_rectangle(play_button.x-(play_button.width/2), play_button.y - (play_button.height / 2), play_button.x + (play_button.width / 2), play_button.y + (play_button.height / 2), al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(exit_button.x - (exit_button.width / 2), exit_button.y - (exit_button.height / 2), exit_button.x + (exit_button.width / 2), exit_button.y + (exit_button.height / 2), al_map_rgb(255, 255, 255));
	al_flip_display();

}

GameStatesEnum MainMenu::get_next_state() {

	return STATE_MAIN_MENU;
}