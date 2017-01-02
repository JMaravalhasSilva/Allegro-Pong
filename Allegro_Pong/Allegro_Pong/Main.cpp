#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "GameState.h"

#ifdef DEBUG_BUILD
#define Debug(x) x
#else
#define Debug(x)
#endif

#define FPS 60






//Initializes all allegro related stuff. Returns true if everything was successful
bool allegro_inits() {
	
	Debug(
		uint32_t version = al_get_allegro_version();
		int major = version >> 24;
		int minor = (version >> 16) & 255;
		int revision = (version >> 8) & 255;
		int release = version & 255;
		std::string str1;
		
		if (release >= 1) {
			str1 = "Version: official ";
		}else{
			str1 = "Version: unofficial ";
		}
		
		std::cout << str1 << major << "." << minor << "." << revision << std::endl;
		)

		
	if (al_init()==false) {
		Debug(std::cout << "al_init() returned false" << std::endl);
		al_show_native_message_box(NULL,"Initialization error","","Failed to initialize the Allegro system",NULL,ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (al_install_keyboard()==false) {
		Debug(std::cout << "al_install_keyboard() returned false" << std::endl);
		al_show_native_message_box(NULL, "Initialization error", "", "Failed to install keyboard driver", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (al_create_display(800, 600)==NULL) {
		Debug(std::cout << "Failed to initialize: al_create_display() returned false" << std::endl);
		al_show_native_message_box(NULL, "Initialization error", "", "Failed to create display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}




	Debug(std::cout << "Initialization successful" << std::endl);
	return true;
}




int  main() {


	if (allegro_inits()==false) {
		return -1;
	}

	
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* gamelooptimer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_display_event_source(al_get_current_display()));



	

	//Enumerators that indicate the current game state
	enum GameStatesEnum {
		STATE_MAIN_MENU,
		STATE_IN_GAME,
		STATE_QUIT
	};

	GameStatesEnum state_flag = STATE_MAIN_MENU;

	GameState* GameLoop = new MainMenu;

	while (state_flag != STATE_QUIT) {

		GameLoop->handle_events();
		GameLoop->logic();
		GameLoop->render();

	}


	/*
	bool quit = false;

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
	
	return 0;
}