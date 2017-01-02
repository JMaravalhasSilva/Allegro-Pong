#include "GameState.h"


//InGame class functions

InGame::InGame() {

	playerscore = 0;
	cpuscore = 0;
	
	ball.Xspeed = 0;
	ball.Yspeed = 0;
	ball.Xposition = SCREEN_WIDTH / 2;
	ball.Yposition = SCREEN_HEIGHT / 2;

	playerpaddle.Yposition = SCREEN_HEIGHT / 2;
	playerpaddle.Yspeed = 0;

	cpupaddle.Yposition = SCREEN_HEIGHT / 2;
	cpupaddle.Yspeed = 0;

}

InGame::~InGame() {

}

void InGame::handle_events() {

}

void InGame::logic() {

}

void InGame::render() {

	//Clear screen
	al_clear_to_color(al_map_rgb(50, 10, 70));

	//Draw player paddle
	al_draw_filled_rectangle(2,playerpaddle.Yposition + 30, 12, playerpaddle.Yposition - 30, al_map_rgb(255, 255, 255));

	//Draw CPU paddle
	al_draw_filled_rectangle(SCREEN_WIDTH-2, cpupaddle.Yposition + 30, SCREEN_WIDTH-12, cpupaddle.Yposition - 30, al_map_rgb(255, 255, 255));

	//Draw ball
	al_draw_filled_circle(ball.Xposition,ball.Yposition,(float) 10, al_map_rgb(255, 255, 255));
	
	al_flip_display();
}

GameStatesEnum InGame::get_next_state() {

	return STATE_IN_GAME;
}