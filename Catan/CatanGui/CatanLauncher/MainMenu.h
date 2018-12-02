#pragma once

#include "../AllegroUI/WindowUI.h"
#include "../../CatanNetworking/CatanNetworking.h"

class CatanLauncher;

class MainMenu : public WindowUI {
public:
	/* Constructor del menu */
	MainMenu(CatanLauncher& _launcher);
private:

	/* Metodos de proceso y callbacks de gui */
	void onExit(void* data);
	void onConnect(void* data);
	void onCancel(void* data);

	/* Procesos alternos */
	virtual void process(void);

	/* Layouts */
	void _data_layout(void);
	void _connecting_layout(void);

	CatanLauncher & launcher;
	CatanNetworking::States prevState;
};