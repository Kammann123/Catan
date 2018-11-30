#pragma once

#include "../AllegroUI/WindowUI.h"

class CatanLauncher;

class MainMenu : public WindowUI {
public:
	MainMenu(CatanLauncher& _launcher);
private:
	CatanLauncher & launcher;
};