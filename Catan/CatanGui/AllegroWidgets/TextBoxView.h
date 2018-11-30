#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "../AllegroUI/TextUI.h"
#include "../AllegroUI/UIView.h"


#define TB_PERC_MARGIN 0.1

#define TB_DEFAULT_BACKGROUND_IDLE_BITMAP "TB_background_idle_bmap.png"
#define TB_DEFAULT_BACKGROUND_SELECTED_BITMAP "TB_background_selected_bmap.png"
#define TB_DEFAULT_BACKGROUND_FOCUSED_BITMAP TB_DEFAULT_BACKGROUND_IDLE_BITMAP
#define TB_DEFAULT_BACKGROUND_DRAGGED_BITMAP TB_DEFAULT_BACKGROUND_SELECTED_BITMAP
#define TB_DEFAULT_TEXT_COLOR 0,0,0
#define TB_DEFAULT_FONT "arial.ttf"

#define TB_BACKGROUND_COLOR "backgroundColor"
#define TB_FONT "font"
#define TB_TEXT_COLOR "text_color"

#define TB_DEFAULT_FONT_SIZE 8

class TextBoxView : public UIView
{
public:
	TextBoxView(TextUI* model_ = nullptr);
	~TextBoxView();
	void draw(void);

};