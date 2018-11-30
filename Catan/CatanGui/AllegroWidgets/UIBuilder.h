#pragma once

#include "../AllegroUI/WindowUI.h"
#include "../AllegroUI/UIComponent.h"

class UIBuilder
{
public:
	/* Métodos de construcción */
	static UIComponent* createSimpleButton(string id, const char* text, size_t height);
};