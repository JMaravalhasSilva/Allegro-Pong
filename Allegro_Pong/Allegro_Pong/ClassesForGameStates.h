#ifndef ALLEGRO_PONG_CLASSES_FOR_GAME_STATES_HEADER
#define ALLEGRO_PONG_CLASSES_FOR_GAME_STATES_HEADER

#include "ProjectHeader.h"

typedef enum GUI_state_enum { PRESSED, NOT_PRESSED, MOUSE_HOVER };

class GuiButton {

	public:
		int x, y,width,height;
		GUI_state_enum state;
		void draw_button(ALLEGRO_COLOR color);

};



//MainMenu classes

class Ball {

	public:
		float Yspeed;
		float Xspeed;
		float Yposition;
		float Xposition;
};

class PlayerPaddle {

	public:
		int Yspeed;
		int Yposition;
};

class CPUPaddle {

	public:
		int Yspeed;
		int Yposition;
};









#endif
