#pragma once
#include "../../AllegroUI/ChildWindowUI.h"
#include "../../../CatanGame/CatanGame.h"


class DiscardWindow : public ChildWindowUI {
public:
	DiscardWindow(string id, CatanGame& _game);

private:
	/***********************
	* Callbacks y acciones *
	***********************/
	void onClose(void* data);
	void onDiscard(void* data);
	void reset(void);

	CatanGame& game;
};