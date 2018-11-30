#pragma once

#include "../AllegroUI/WindowUI.h"
#include "../AllegroUI/UIComponent.h"

class UIBuilder
{
public:
	/* M�todos de construcci�n */
	static UIComponent* createButton(string id, const char* focused, const char* selected, const char* idle, WindowUI* interface_);
	static UIComponent* createTextField(ALLEGRO_FONT * font_, size_t width, size_t height, ALLEGRO_COLOR textColor_, WindowUI* interface_, string id, size_t size, TextUI::Mode mode);
	static UIComponent* createSimpleButton(string id, const char* text, size_t height);
};