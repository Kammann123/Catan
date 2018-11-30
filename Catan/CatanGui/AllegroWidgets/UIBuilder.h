#pragma once
#include "../AllegroWidgets/ButtonView.h"
#include "../AllegroWidgets/TextFieldView.h"

#include "../AllegroUI/MouseUI.h"
#include "../AllegroUI/TextUI.h"

#include "../AllegroUI/MouseController.h"
#include "../AllegroUI/TextController.h"

#include "../AllegroUI/WindowUI.h"
#include "../AllegroUI/UIComponent.h"

class UIBuilder
{
public:
	UIBuilder();
	~UIBuilder();

	/* Métodos de construcción */
	static UIComponent* createButton(string id, const char* focused, const char* selected, const char* idle, WindowUI* interface_);
	static UIComponent* createTextField(ALLEGRO_FONT * font_, ALLEGRO_COLOR textColor_, WindowUI* interface_, string id, size_t size, TextUI::Mode mode);

private:

};