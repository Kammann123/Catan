#pragma once
#include "../AllegroUI/FrameUI.h"
#include "allegro5/allegro.h"
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/MouseUI.h"
#include "../AllegroUI/WindowUI.h"

#define DEFAULT_IDLE_SAMPLE ""
#define DEFAULT_SELECTED_SAMPLE ""
#define DEFAULT_FOCUSED_SAMPLE "..\Sounds\sound1.mp3"
#define DEFAULT_DRAGGED_SAMPLE DEFAULT_SELECTED_SAMPLE

class SoundStatusView : public UIView
{
public:
	SoundStatusView(MouseUI* model_ = nullptr);
	void draw(void);
private:
	MouseUI::Status prevStatus;
};