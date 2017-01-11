#include "ClassesForGameStates.h"

void GuiButton::draw_button(ALLEGRO_COLOR color) {

	al_draw_filled_rectangle(this->x - (this->width / 2), this->y - (this->height / 2), this->x + (this->width / 2), this->y + (this->height / 2),color);

}