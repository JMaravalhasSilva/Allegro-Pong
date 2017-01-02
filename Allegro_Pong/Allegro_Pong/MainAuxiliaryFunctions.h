#ifndef ALLEGRO_PONG_MAIN_AUXILIARY_FUNCTIONS_HEADER
#define ALLEGRO_PONG_MAIN_AUXILIARY_FUNCTIONS_HEADER

#include "ProjectHeader.h"
#include "GameState.h"

//Function that changes the GameState based on what the next state is, and returns the chosen state
GameStatesEnum change_gameloop_state(GameState* GameLoop, GameStatesEnum next_state);

//Initializes all allegro related stuff. Returns true if everything was successful
bool allegro_inits(ALLEGRO_TIMER** gamelooptimer, ALLEGRO_EVENT_QUEUE** timer_event_queue);

//Caps the framerate to whatever the timer is configured to. Returns false if a timer error occurs
bool frame_capping(ALLEGRO_EVENT_QUEUE* timer_event_queue);

#endif