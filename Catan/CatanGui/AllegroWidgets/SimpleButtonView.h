#pragma once

#include "../AllegroUI/UIView.h"
#include "../AllegroUI/TextUI.h"
#include "../AllegroUI/MouseController.h"
#include "../AllegroUI/TextController.h"
#include "../AllegroUI/TextConfig.h"
#include "../AllegroUI/ColorConfig.h"

#define SIMPLE_BUTTON_TEXTCOLOR	"textcolor"
#define DEFAULT_SP_TEXTCOLOR	0, 0, 0

#define SIMPLE_BUTTON_TEXTFONT	"textfont"
#define DEFAULT_SP_TEXTFONT		"LOVES.ttf"
#define DEFAULT_SP_TEXTSIZE		10

#define PADDING_X	5
#define PADDING_Y	5

class SimpleButtonView : public UIView {
public:
	SimpleButtonView(WindowUI* interface_, UIModel* model_);
	~SimpleButtonView();
	virtual void draw(void);
};