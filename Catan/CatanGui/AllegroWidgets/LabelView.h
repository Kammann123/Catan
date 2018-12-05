#pragma once
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/TextUI.h"

#define LA_DEFAULT_TEXT_COLOR   255, 255, 255
#define LA_DEFAULT_FONT_SIZE 14
#define LA_DEFAULT_FONT "CatanGui\\Fonts\\Hack-Regular.ttf"

#define LA_FONT "font"
#define LA_TEXT_COLOR "text_color"

class LabelView : public UIView
{
public:
	LabelView(TextUI* model_ = nullptr);
	~LabelView();
	void draw(void);
};