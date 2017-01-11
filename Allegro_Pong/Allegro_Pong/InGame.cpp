#include "GameState.h"


enum PlayerActions {
	GO_UP,GO_DOWN,EXITGAME
};


//InGame class functions

InGame::InGame() {

	playerscore = 0;
	cpuscore = 0;
	
	ball.Xspeed = (-5) + (rand() % (int)(5 - (-5) + 1));
	ball.Yspeed = (-5) + (rand() % (int)(5 - (-5) + 1));

	if (ball.Xspeed == 0) {
		ball.Xspeed = 1;
	}

	ball.Xposition = SCREEN_WIDTH / 2;
	ball.Yposition = SCREEN_HEIGHT / 2;

	playerpaddle.Yposition = SCREEN_HEIGHT / 2;
	playerpaddle.Yspeed = 0;

	cpupaddle.Yposition = SCREEN_HEIGHT / 2;
	cpupaddle.Yspeed = 0;

	for (int i = 0; i <= 2; i++) {
		actions[i] = false;
	}

	keyboard_event_queue = al_create_event_queue();
	al_register_event_source(keyboard_event_queue, al_get_keyboard_event_source());

	font = al_load_ttf_font("arial.ttf", 30, 0);


}

InGame::~InGame() {

	al_destroy_font(font);

	//There is no need to unregister the queue because Allegro takes care of that automatically
	al_destroy_event_queue(keyboard_event_queue);

}

void InGame::handle_events() {

	ALLEGRO_EVENT keyboard_event;

	//Get all keyboard events
	while (al_is_event_queue_empty(keyboard_event_queue) == false) {

		al_get_next_event(keyboard_event_queue, &keyboard_event);

		switch (keyboard_event.type) {

		//If a key was pressed
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (keyboard_event.keyboard.keycode) {
			
			//UP or W 
			case ALLEGRO_KEY_UP:
			case ALLEGRO_KEY_W:
				actions[GO_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_S:
				actions[GO_DOWN] = true;
				break;

			case ALLEGRO_KEY_ESCAPE:
				actions[EXITGAME] = true;

			default:
				break;

			}
			break;

		//If a key was released
		case ALLEGRO_EVENT_KEY_UP:
			switch (keyboard_event.keyboard.keycode) {

				//UP or W 
			case ALLEGRO_KEY_UP:
			case ALLEGRO_KEY_W:
				actions[GO_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_S:
				actions[GO_DOWN] = false;
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

void InGame::logic() {

	if (actions[EXITGAME] == true) {
		return;
	}

	//Add speeds to player. Positive Y is down! 
	if (actions[GO_UP] == true) {
		playerpaddle.Yspeed -= 1;
	}

	if (actions[GO_DOWN] == true) {
		playerpaddle.Yspeed += 1;
	}

	//Brakes the paddle when player is not pressing anything
	if (actions[GO_DOWN] == false && actions[GO_UP] == false) {
		if (playerpaddle.Yspeed>0) {
			playerpaddle.Yspeed -= 1;
		}
		else if(playerpaddle.Yspeed<0){
			playerpaddle.Yspeed += 1;
		}
		
	}

	//Add speeds to CPU
	//CPU will always try to go after the current ball position.
	//Remember that negative Y is up and positive Y is down!
	if ((ball.Yposition - cpupaddle.Yposition) < 0) {
		cpupaddle.Yspeed -= 1;
	}else if ((ball.Yposition - cpupaddle.Yposition) > 0) {
		cpupaddle.Yspeed += 1;
	}

	//Cap player speed
	if (playerpaddle.Yspeed > 30) {
		playerpaddle.Yspeed = 30;
	}else if (playerpaddle.Yspeed < -30) {
		playerpaddle.Yspeed = -30;
	}

	//Cap CPU speed
	if (cpupaddle.Yspeed > 20) {
		cpupaddle.Yspeed = 20;
	}
	else if (cpupaddle.Yspeed < -20) {
		cpupaddle.Yspeed = -20;
	}

	
	//Move player
	playerpaddle.Yposition += playerpaddle.Yspeed;

	//Cap player position
	if (playerpaddle.Yposition > SCREEN_HEIGHT - 30) {
		playerpaddle.Yposition = SCREEN_HEIGHT - 30;
		playerpaddle.Yspeed = 0;
	}else if (playerpaddle.Yposition < 30) {
		playerpaddle.Yposition = 30;
		playerpaddle.Yspeed = 0;
	}

	//Move CPU
	cpupaddle.Yposition += cpupaddle.Yspeed;

	//Cap CPU position
	if (cpupaddle.Yposition > SCREEN_HEIGHT - 30) {
		cpupaddle.Yposition = SCREEN_HEIGHT - 30;
		cpupaddle.Yspeed = 0;
	}
	else if (cpupaddle.Yposition < 30) {
		cpupaddle.Yposition = 30;
		cpupaddle.Yspeed = 0;
	}

	//Cap ball Y speed so that game doesn't become impossible to play ;)
	if (ball.Yspeed >= 30) {
		ball.Yspeed = 30;
	}

	//Move ball
	ball.Xposition += ball.Xspeed;
	ball.Yposition += ball.Yspeed;

	//Ball colision with walls
	if ( (ball.Yposition >= SCREEN_HEIGHT - 10) || (ball.Yposition <= 10) ) {
		ball.Yspeed = -ball.Yspeed;
	}

	//Ball colision with CPU paddle
	if (ball.Xposition >= SCREEN_WIDTH - 12 - 10) {
		
		//if X position is suitable for ball collision, check Y position (+-3 adds some tolerance to colision)
		if (ball.Yposition >= cpupaddle.Yposition - 30 - 3 && ball.Yposition <= cpupaddle.Yposition + 30 + 3) {
			//Invert X speed and increase 1
			ball.Xspeed = -ball.Xspeed -1; 
			//Add some Y speed to the ball
			ball.Yspeed += 0.2*cpupaddle.Yspeed;

			//Reset ball position so it doesn't collide with the paddle again
			ball.Xposition = SCREEN_WIDTH - 12 - 10;
		}
			

	}

	//Ball colision with player paddle
	if (ball.Xposition <= 12) {

		//if X position is suitable for ball collision, check Y position
		if (ball.Yposition >= playerpaddle.Yposition - 30 - 3 && ball.Yposition <= playerpaddle.Yposition + 30 + 3) {
			//Invert X speed and increase 1
			ball.Xspeed = -ball.Xspeed + 1;
			//Add some Y speed to the ball
			ball.Yspeed += 0.2*playerpaddle.Yspeed;

			//Reset ball position so it doesn't collide with the paddle again
			ball.Xposition = 12 ;
		}


	}


	if ((ball.Xposition >= SCREEN_WIDTH - 10)) {
		
		ball.Xspeed = (-5) + (rand() % (int)(5 - (-5) + 1));
		ball.Yspeed = (-5) + (rand() % (int)(5 - (-5) + 1));

		ball.Xposition = SCREEN_WIDTH / 2;
		ball.Yposition = SCREEN_HEIGHT / 2;

		playerscore += 1;
	}

	if ((ball.Xposition < 10)) {
		
		ball.Xspeed = (-5) + (rand() % (int)(5 - (-5) + 1));
		ball.Yspeed = (-5) + (rand() % (int)(5 - (-5) + 1));

		ball.Xposition = SCREEN_WIDTH / 2;
		ball.Yposition = SCREEN_HEIGHT / 2;

		cpuscore += 1;
	}

	//Small correction in case the Xspeed is zero due to random number generation
	if (ball.Xspeed == 0) {
		ball.Xspeed = 1;
	}



}

void InGame::render() {
	std::string score;

	//Clear screen
	al_clear_to_color(al_map_rgb(50, 10, 70));

	//Show scores
	score = std::to_string(playerscore);
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 7), ALLEGRO_ALIGN_CENTRE, (score.c_str()));
	score = std::to_string(cpuscore);
	al_draw_text(font, al_map_rgb(255, 255, 255), 3 * (SCREEN_WIDTH / 4), (SCREEN_HEIGHT / 7), ALLEGRO_ALIGN_CENTRE, (score.c_str()));

	//Draw player paddle
	al_draw_filled_rectangle(2,playerpaddle.Yposition + 30, 12, playerpaddle.Yposition - 30, al_map_rgb(255, 255, 255));

	//Draw CPU paddle
	al_draw_filled_rectangle(SCREEN_WIDTH-2, cpupaddle.Yposition + 30, SCREEN_WIDTH-12, cpupaddle.Yposition - 30, al_map_rgb(255, 255, 255));

	//Draw ball
	al_draw_filled_circle(ball.Xposition,ball.Yposition,(float) 10, al_map_rgb(255, 255, 255));
	
	al_flip_display();
}

GameStatesEnum InGame::get_next_state() {

	if (actions[EXITGAME] == true) {
		return STATE_MAIN_MENU;
	}


	return STATE_IN_GAME;
}