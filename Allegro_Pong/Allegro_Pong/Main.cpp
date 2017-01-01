#include <iostream>
#include <string>
#include <allegro5/allegro.h>

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

		
	if (!al_init()) {
		Debug( std::cout << "Failed to initialize: al_init() returned false" << std::endl );
		return false;
	}

	if (!al_install_keyboard()) {
		Debug(std::cout << "Failed to initialize: al_install_keyboard() returned false" << std::endl);
		return false;
	}

	if (!al_create_display(800, 600)) {
		Debug(std::cout << "Failed to initialize: al_create_display() returned false" << std::endl);
		return false;
	}




	Debug(std::cout << "Initialization successful" << std::endl);
	return true;
}


int  main() {


	if (!allegro_inits()) {
		return -1;
	}

	

	

	ALLEGRO_TIMER* gamelooptimer = al_create_timer(1.0 / FPS);


	while (1);

	return 0;
}