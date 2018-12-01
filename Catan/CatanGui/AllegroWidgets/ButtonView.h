#pragma once
#include "../AllegroUI/FrameUI.h"
#include "allegro5/allegro.h"
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/MouseUI.h"
#include "../AllegroUI/WindowUI.h"

#define NO_FLAGS 0
#define NO_ROTATION 0

#define DEFAULT_IDLE_BITMAP "CatanGui\\Buttons\\BUTTON_IDLE.png"
#define DEFAULT_SELECTED_BITMAP "CatanGui\\Buttons\\BUTTON_SELECTED.png"
#define DEFAULT_FOCUSED_BITMAP "CatanGui\\Buttons\\BUTTON_FOCUSED.png"
#define DEFAULT_DRAGGED_BITMAP DEFAULT_SELECTED_BITMAP

class ButtonView : public UIView
{
public:
	ButtonView(MouseUI* model_ = nullptr);
	void updateModelValues(void);
	void draw(void);
};