#pragma once

#include "../AllegroUI/WindowUI.h"
#include "../AllegroUI/UIComponent.h"

class UIBuilder
{
public:
	/* M�todos de construcci�n */
	static UIComponent* createSimpleButton(string id, const char* text, size_t height);
};