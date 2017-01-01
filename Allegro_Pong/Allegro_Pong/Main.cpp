#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

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

	

	

	ALLEGRO_TIMER* gamelooptimer = al_create_timer(1.0 / FPS);


	while (1);

	return 0;
}