#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "../AllegroUI/TextUI.h"
#include "../AllegroUI/UIView.h"

#define TF_PERC_MARGIN 0.1

#define TF_DEFAULT_BACKGROUND_IDLE_COLOR 255, 255, 255
#define TF_DEFAULT_BACKGROUND_SELECTED_COLOR 111,111,0
#define TF_DEFAULT_BACKGROUND_FOCUSED_COLOR TF_DEFAULT_BACKGROUND_IDLE_COLOR
#define TF_DEFAULT_BACKGROUND_DRAGGED_COLOR TF_DEFAULT_BACKGROUND_SELECTED_COLOR 
#define TF_DEFAULT_TEXT_COLOR 0, 0, 0
#define TF_DEFAULT_FONT  "CatanGui\\Fonts\\NewAmsterdam.ttf"

#define TF_BACKGROUND_COLOR "backgroundColor"
#define TF_FONT "font"
#define TF_TEXT_COLOR "text_color"

#define TF_DEFAULT_FONT_SIZE 15

#define TF_PADDING_Y 3
#define TF_PADDING_X 3

class TextFieldView : public UIView
{
public:
	TextFieldView (TextUI* model_ = nullptr);
	~TextFieldView();
	void draw(void);
	void updateModelValues(void);
};