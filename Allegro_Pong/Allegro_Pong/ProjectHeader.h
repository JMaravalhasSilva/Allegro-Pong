#ifndef ALLEGRO_PONG_PROJECT_HEADER
#define ALLEGRO_PONG_PROJECT_HEADER


	#include <iostream>
	#include <string>
	#include <random>
	#include <allegro5/allegro.h>
	#include <allegro5/allegro_native_dialog.h>
	#include <allegro5/allegro_font.h>
	#include <allegro5/allegro_ttf.h>
	#include <allegro5/allegro_primitives.h>

	#ifdef DEBUG_BUILD
		#define Debug(x) x
	#else
		#define Debug(x)
	#endif

	#define FPS 60

	#define SCREEN_WIDTH  800
	#define SCREEN_HEIGHT 600



#endif
