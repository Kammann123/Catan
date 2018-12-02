#pragma once

#include "../AllegroUI/WindowUI.h"

class CatanLauncher;

class GameMenu : public WindowUI {
public:
	GameMenu(CatanLauncher& _launcher);
private:
	CatanLauncher & launcher;
};