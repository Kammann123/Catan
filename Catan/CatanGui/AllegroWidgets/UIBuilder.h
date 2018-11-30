#pragma once

#include "../AllegroUI/WindowUI.h"
#include "../AllegroUI/UIComponent.h"
#include "../AllegroUI/TextUI.h"


class UIBuilder
{
public:
	/* Métodos de construcción */
	static UIComponent* createButton(string id);
	static UIComponent* createTextField(size_t height, string id, size_t size, TextUI::Mode mode);
	static UIComponent* createSimpleButton(string id, const char* text, size_t height);

};