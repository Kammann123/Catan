#pragma once
#include "../../MVC/Observer.h"
#include "../AllegroUI/FrameUI.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "TextField.h"


#define DEFAULT_FONT		al_load_ttf_font("arial.ttf",10,0)
#define DEFAULT_TEXT_COLOR	al_map_rgb(0,0,0)
#define IDLE_BACK_COLOR		al_map_rgb(255,255,255)
#define FOCUSED_BACK_COLOR	al_map_rgb(220,220,220)
#define SELECTED_BACK_COLOR	al_map_rgb(0,255,0)


class TextFieldView : public Observer
{
public:
	TextFieldView(TextField& model_);
	~TextFieldView();
	void update(void);

private:
	TextField& model;
	ALLEGRO_DISPLAY* display;
};