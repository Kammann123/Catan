#pragma once
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/TextUI.h"

#define MLA_DEFAULT_TEXT_COLOR   0, 0, 0
#define MLA_DEFAULT_FONT_SIZE 13
#define MLA_DEFAULT_FONT "CatanGui\\Fonts\\Hack-Regular.ttf"

#define MLA_FONT "font"
#define MLA_TEXT_COLOR "text_color"

class MultiLabelView : public UIView{
public:
	MultiLabelView(TextUI* model_ = nullptr);
	void draw(void);
	void setWidth(double width);
	void setHeight(double height);
private:
	double width;
	double height;
};