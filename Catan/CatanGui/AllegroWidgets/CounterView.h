#pragma once
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/CounterUI.h"

#define CLA_DEFAULT_TEXT_COLOR   100, 220, 255
#define CLA_DEFAULT_FONT_SIZE 25
#define CLA_DEFAULT_FONT "CatanGui\\Fonts\\SuperMario256.ttf"

#define CLA_FONT "font"
#define CLA_TEXT_COLOR "text_color"

class CounterView : public UIView{
public:
	CounterView(CounterUI* model_ = nullptr);
	void draw(void);
};