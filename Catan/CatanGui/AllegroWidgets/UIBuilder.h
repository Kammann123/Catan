#pragma once

#include "../AllegroUI/WindowUI.h"
#include "../AllegroUI/UIComponent.h"
#include "../AllegroUI/TextUI.h"

class UIBuilder
{
public:
	/* Métodos de construcción de componentes
	* para la interfaz grafica 
	*/
	static UIComponent* createButton(string id);
	static UIComponent* createTextField(string id, size_t size, TextUI::Mode mode=TextUI::Mode::EVERYTHING);
	static UIComponent* createSimpleButton(string id, const char* text, size_t height);
	static UIComponent* createTextBox(string id, size_t size, TextUI::Mode mode = TextUI::Mode::EVERYTHING);
	static UIComponent* createLabel(string id, size_t size);
	
	/* Expansion de funcionalidades para los elementos y componentes
	* de la interfaz grafica
	*/
	static UIComponent* attachSample(UIComponent * component);
};