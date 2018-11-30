#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "../AllegroUI/TextUI.h"
#include "../AllegroUI/UIView.h"


#define PERC_MARGIN 0.1

#define DEFAULT_BACKGROUND_IDLE_COLOR 255,255,255
#define DEFAULT_BACKGROUND_SELECTED_COLOR 0,255,0
#define DEFAULT_BACKGROUND_FOCUSED_COLOR 220,220,220
#define DEFAULT_BACKGROUND_DRAGGED_COLOR DEFAULT_BACKGROUND_SELECTED_COLOR 
#define DEFAULT_TEXT_COLOR 0,0,0
#define DEFAULT_FONT "arial.ttf"

#define BACKGROUND_COLOR "backgroundColor"
#define FONT "font"
#define TEXT_COLOR "text_color"

#define DEFAULT_FONT_SIZE 8

class TextFieldView : public UIView
{
public:
	TextFieldView (TextUI* model_, WindowUI* interface_);
	~TextFieldView();
	void draw(void);

};