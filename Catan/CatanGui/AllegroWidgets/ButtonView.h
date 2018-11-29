#pragma once
#include "../../MVC/Observer.h"
#include "../AllegroUI/FrameUI.h"
#include "allegro5/allegro.h"

#define NO_FLAGS 0
#define NO_ROTATION 0

class ButtonView : public Observer
{
public:
	ButtonView(ALLEGRO_BITMAP* focused, ALLEGRO_BITMAP* selected, ALLEGRO_BITMAP* idle, ALLEGRO_DISPLAY* display_, FrameUI& model_);
	void update(void);

private:
	FrameUI& model;
	ALLEGRO_BITMAP* focusedBitmap;
	ALLEGRO_BITMAP* selectedBitmap;
	ALLEGRO_BITMAP* idleBitmap;
	ALLEGRO_DISPLAY* display;
};