#include "MainAuxiliaryFunctions.h"


//Function that changes the GameState based on what the next state is, and returns the chosen state
GameStatesEnum change_gameloop_state(GameState* GameLoop, GameStatesEnum next_state) {

	switch (next_state) {

	case STATE_MAIN_MENU:

		break;

	case STATE_IN_GAME:

		break;

	case STATE_QUIT:

		break;

	}


	return next_state;

}





//Initializes all allegro related stuff. Returns true if everything was successful
bool allegro_inits(ALLEGRO_TIMER** gamelooptimer, ALLEGRO_EVENT_QUEUE** timer_event_queue) {

	Debug(
		uint32_t version = al_get_allegro_version();
	int major = version >> 24;
	int minor = (version >> 16) & 255;
	int revision = (version >> 8) & 255;
	int release = version & 255;
	std::string str1;

	if (release >= 1) {
		str1 = "Version: official ";
	}
	else {
		str1 = "Version: unofficial ";
	}

	std::cout << str1 << major << "." << minor << "." << revision << std::endl;
	)


		if (al_init() == false) {
			Debug(std::cout << "al_init() returned false" << std::endl);
			al_show_native_message_box(NULL, "Initialization error", "", "Failed to initialize the Allegro system", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return false;
		}

	if (al_install_keyboard() == false) {
		al_show_native_message_box(NULL, "Initialization error", "", "Failed to install keyboard driver", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT) == NULL) {
		al_show_native_message_box(NULL, "Initialization error", "", "Failed to create display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_primitives_addon()) {
		al_show_native_message_box(NULL, "Initialization error", "", "Failed to initialize primitives", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//*gamelooptimer accesses the pointer variable whose own address is passed to this function, thus the pointer will point to the new ALLEGRO_TIMER
	*gamelooptimer = al_create_timer(1.0 / FPS);
	if (*gamelooptimer == NULL) {
		Debug(std::cout << "al_create_timer() returned NULL" << std::endl);
		al_show_native_message_box(NULL, "Initialization error", "", "Failed to initialize timer", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	*timer_event_queue = al_create_event_queue();
	if (*timer_event_queue == NULL) {
		Debug(std::cout << "al_create_event_queue() returned NULL" << std::endl);
		al_show_native_message_box(NULL, "Initialization error", "", "Failed to initialize timer event queue", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_register_event_source(*timer_event_queue, al_get_timer_event_source(*gamelooptimer));

	Debug(std::cout << "Initialization successful" << std::endl);
	return true;
}





//Caps the framerate to whatever the timer is configured to. Returns false if a timer error occurs
bool frame_capping(ALLEGRO_EVENT_QUEUE* timer_event_queue) {

	ALLEGRO_EVENT timer_event;

	//Waits for the gamelooptimer to increment
	while (al_is_event_queue_empty(timer_event_queue) == true);

	al_get_next_event(timer_event_queue, &timer_event);

	//Timers should only generate events of the type ALLEGRO_EVENT_TIMER, so this is an overzealous check (that also clears the event from the queue)
	if (timer_event.type != ALLEGRO_EVENT_TIMER) {
		Debug(std::cout << "timer_event.type is not an ALLEGRO_EVENT_TIMER" << std::endl;)
			al_show_native_message_box(NULL, "Timer error", "", "Timer has generated something that is not an increment", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//If the game is running slower than 60FPSs, this will flush the queue to avoid overflows
	if (al_is_event_queue_empty(timer_event_queue) == false) {
		al_flush_event_queue(timer_event_queue);
	}


	return true;
}