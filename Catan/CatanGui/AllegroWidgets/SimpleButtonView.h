#pragma once

#include "../AllegroUI/UIView.h"
#include "../AllegroUI/TextUI.h"
#include "../AllegroUI/MouseController.h"
#include "../AllegroUI/TextController.h"
#include "../AllegroUI/TextConfig.h"
#include "../AllegroUI/ColorConfig.h"

class SimpleButtonView : public UIView {
public:
	SimpleButtonView(WindowUI* interface_, UIModel* model_);
	~SimpleButtonView();
	virtual void draw(void);
};