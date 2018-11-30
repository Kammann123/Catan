#pragma once
#include "../AllegroUI/FrameUI.h"
#include "allegro5/allegro.h"
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/MouseUI.h"
#include "../AllegroUI/WindowUI.h"


class SoundStatusView : public UIView
{
public:
	SoundStatusView(MouseUI* model_ = nullptr);
	void draw(void);
private:
	MouseUI::Status prevStatus;
};