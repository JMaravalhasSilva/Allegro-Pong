#include "Main.h"





int  main() {
	ALLEGRO_TIMER* gamelooptimer = NULL;
	ALLEGRO_EVENT_QUEUE* timer_event_queue = NULL;
	GameStatesEnum current_state = STATE_IN_GAME, next_state = STATE_IN_GAME;

	if (allegro_inits(&gamelooptimer, &timer_event_queue)==false) {
		return -1;
	}

	al_start_timer(gamelooptimer);
	
	GameState* GameLoop = new InGame;

	while (current_state != STATE_QUIT) {

		GameLoop->handle_events();
		GameLoop->logic();
		GameLoop->render();

		next_state=GameLoop->get_next_state();

		if (next_state  != current_state ) {
			current_state=change_gameloop_state(GameLoop,next_state);
		}
		

		if (frame_capping(timer_event_queue) == false) {
			return -1;
		}
		

	}

	delete GameLoop;
	
	return 0;
}



//This code was used to display messages on the screen
/*

al_init_font_addon();
al_init_ttf_addon();

ALLEGRO_FONT *font = al_load_ttf_font("arial.ttf", 72, 0);
if (!font) {
Debug(std::cout << "Font failed!" << std::endl;)
return -1;
}

//...

//This would go in the main loop:
al_clear_to_color(al_map_rgb(50, 10, 70));
al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 4), ALLEGRO_ALIGN_CENTRE, "Trying hard");

al_flip_display();
*/



//This code was used to detect if the display was closed
/*

ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
al_register_event_source(event_queue, al_get_display_event_source(al_get_current_display()));

bool quit = false;

//This was the old main loop
while (quit==false) {

if (!al_is_event_queue_empty(event_queue)) {
ALLEGRO_EVENT event;
al_get_next_event(event_queue, &event);
Debug(std::cout << "Detected display event" << std::endl;)

if (event.type==ALLEGRO_EVENT_DISPLAY_CLOSE) {
quit = true;
}
}



}
*/