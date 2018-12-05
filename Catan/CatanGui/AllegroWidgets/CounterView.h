#pragma once
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/CounterUI.h"

#define LA_DEFAULT_TEXT_COLOR   100, 220, 255
#define LA_DEFAULT_FONT_SIZE 25
#define LA_DEFAULT_FONT "CatanGui\\Fonts\\SuperMario256.ttf"

#define LA_FONT "font"
#define LA_TEXT_COLOR "text_color"

class CounterView : public UIView{
public:
	CounterView(CounterUI* model_ = nullptr);
	void draw(void);
};