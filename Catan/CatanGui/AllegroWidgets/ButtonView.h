#pragma once
#include "../AllegroUI/FrameUI.h"
#include "allegro5/allegro.h"
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/MouseUI.h"
#include "../AllegroUI/WindowUI.h"

#define NO_FLAGS 0
#define NO_ROTATION 0

class ButtonView : public UIView
{
public:
	ButtonView(ALLEGRO_BITMAP* focused, ALLEGRO_BITMAP* selected, ALLEGRO_BITMAP* idle, WindowUI* interface_, MouseUI* model_);
	void update(void);
	void draw(void);

private:
	ALLEGRO_BITMAP* focusedBitmap;
	ALLEGRO_BITMAP* selectedBitmap;
	ALLEGRO_BITMAP* idleBitmap;
};