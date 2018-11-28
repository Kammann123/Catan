#pragma once
#include <allegro5/allegro.h>


class Controller
{
public:
	Controller() {};
	~Controller() {};
	virtual void parseMouseEvent(ALLEGRO_EVENT* ev_) = 0;
	virtual void parseKeyboardEvent(ALLEGRO_EVENT* ev) = 0;
};