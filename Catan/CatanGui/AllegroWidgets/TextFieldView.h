#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "../AllegroUI/TextUI.h"
#include "../AllegroUI/UIView.h"


#define IDLE_COLOR al_map_rgb(255, 255, 255)
#define SELECTED_COLOR al_map_rgb(0, 255, 0)
#define FOCUSED_COLOR al_map_rgb(220, 220, 220)
#define PERC_MARGIN 0.1


class TextFieldView : public UIView
{
public:
	TextFieldView(ALLEGRO_FONT* font_, ALLEGRO_COLOR textColor_, TextUI* model_, WindowUI* interface_);
	~TextFieldView();
	void draw(void);

private:
	ALLEGRO_FONT* font;
	ALLEGRO_COLOR backgroundColor;
	ALLEGRO_COLOR textColor;
};