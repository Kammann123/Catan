#pragma once

#include "../../AllegroUI/ChildWindowUI.h"
#include "../../CatanLauncher/CatanLauncher.h"

class ErrorWindow : public ChildWindowUI {
public:
	ErrorWindow(string id, CatanLauncher& _launcher);

private:
	/***********************
	* Callbacks y acciones *
	***********************/
	void onOk(void* data);

	CatanLauncher& launcher;
};