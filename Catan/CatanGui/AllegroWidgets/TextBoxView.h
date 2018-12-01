#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "../AllegroUI/TextUI.h"
#include "../AllegroUI/UIView.h"


#define TB_PERC_MARGIN 0.1

#define TB_DEFAULT_BACKGROUND_IDLE_BITMAP "CatanGui\\TextBox\\TextBoxIdle.png"
#define TB_DEFAULT_BACKGROUND_SELECTED_BITMAP "CatanGui\\TextBox\\TextBox.png"
#define TB_DEFAULT_BACKGROUND_FOCUSED_BITMAP TB_DEFAULT_BACKGROUND_IDLE_BITMAP
#define TB_DEFAULT_BACKGROUND_DRAGGED_BITMAP TB_DEFAULT_BACKGROUND_SELECTED_BITMAP
#define TB_DEFAULT_TEXT_COLOR 0,0,0
#define TB_DEFAULT_FONT "CatanGui\\Fonts\\NewAmsterdam.ttf"

#define TB_BACKGROUND_COLOR "backgroundColor"
#define TB_FONT "font"
#define TB_TEXT_COLOR "text_color"

#define TB_DEFAULT_FONT_SIZE 80

#define TB_PADDING_X	10
#define TB_PADDING_Y	10

class TextBoxView : public UIView
{
public:
	TextBoxView(TextUI* model_ = nullptr);
	~TextBoxView();
	void draw(void);

};