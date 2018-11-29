#pragma once

#include "../../MVC/Observer.h"
#include "../AllegroUI/FrameUI.h"
#include "allegro5/allegro.h"
#include "Label.h"


#define DEFAULT_FONT		al_load_ttf_font("arial.ttf",10,0)
#define DEFAULT_TEXT_COLOR	al_map_rgb(0,0,0)
#define DEFAULT_BACK_COLOR	al_map_rgb(255,255,255)

class LabelView : public Observer
{
public:
	LabelView(Label& model_);
	~LabelView();
	void update(void);

private:
	Label& model;
	ALLEGRO_DISPLAY* display;
};