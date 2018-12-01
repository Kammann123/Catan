#pragma once

#include "allegro5/allegro.h"
#include "../AllegroUI/UIView.h"
#include "../AllegroUI/MouseUI.h"

#define DEFAULT_FOCUSED_SAMPLE "CatanGui\\Sounds\\throat.wav"

class SoundStatusView : public UIView
{
public:
	SoundStatusView(MouseUI* model_ = nullptr);
	void draw(void);
	void updateModelValues(void);
private:
	MouseUI::Status prevStatus;
	bool isPlaying;
	ALLEGRO_SAMPLE_ID music;
};