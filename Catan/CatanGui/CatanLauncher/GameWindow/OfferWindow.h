#pragma once
#include "../../AllegroUI/ChildWindowUI.h"
#include "../../../CatanGame/CatanGame.h"

class OfferWindow : public ChildWindowUI {
public:
	OfferWindow(string id, CatanGame& _game);

private:
	/***********************
	* Callbacks y acciones *
	***********************/
	void onClose(void* data);
	void onTrade(void* data);
	void reset(void);

	CatanGame& game;
};