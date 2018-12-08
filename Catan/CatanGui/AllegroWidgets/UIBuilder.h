#pragma once

#include "../AllegroUI/WindowUI.h"
#include "../AllegroUI/UIComponent.h"
#include "../AllegroUI/TextUI.h"
#include "../AllegroUI/CounterUI.h"

class UIBuilder
{
public:
	/* Métodos de construcción de componentes
	* para la interfaz grafica 
	*/
	static UIComponent* createTextField(string id, size_t size, TextUI::Mode mode=TextUI::Mode::EVERYTHING);
	static UIComponent* createTextBox(string id, size_t size, TextUI::Mode mode = TextUI::Mode::EVERYTHING);
	static UIComponent* createSimpleButton(string id, const char* text, size_t height);
	static UIComponent* createMultiLabel(string id, double width, double height);
	static UIComponent* createCounterBox(string id, unsigned int max);
	static UIComponent* createCounter(string id, unsigned int max);
	static UIComponent* createLabel(string id, size_t size);
	static UIComponent* createButton(string id);
	static UIComponent* createImage(string id);
	
	/* Expansion de funcionalidades para los elementos y componentes
	* de la interfaz grafica
	*/
	static UIComponent* attachSample(UIComponent * component);
};