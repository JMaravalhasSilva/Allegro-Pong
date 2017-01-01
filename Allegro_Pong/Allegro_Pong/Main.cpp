#include <iostream>
#include <allegro5/allegro.h>

#ifdef DEBUG_BUILD
#define Debug(x) x
#else
#define Debug(x)
#endif

#define FPS 60

int  main() {

	al_init();
	al_install_keyboard();
	al_create_display(800, 600);

	Debug(std::cout << "Ola lol" << std::endl;)

	ALLEGRO_TIMER* gamelooptimer = al_create_timer(1.0 / FPS);


	while (1);

	return 0;
}