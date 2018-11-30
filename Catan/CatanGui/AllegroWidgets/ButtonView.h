#pragma once
#include "../AllegroUI/FrameUI.h"
#include "allegro5/allegro.h"
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/MouseUI.h"
#include "../AllegroUI/WindowUI.h"

#define NO_FLAGS 0
#define NO_ROTATION 0

#define DEFAULT_IDLE_BITMAP "llenar esto"
#define DEFAULT_SELECTED_BITMAP "llenar esto"
#define DEFAULT_FOCUSED_BITMAP "llenar esto"
#define DEFAULT_DRAGGED_BITMAP DEFAULT_SELECTED_BITMAP

class ButtonView : public UIView
{
public:
	ButtonView(MouseUI* model_ = nullptr);
	void draw(void);
};