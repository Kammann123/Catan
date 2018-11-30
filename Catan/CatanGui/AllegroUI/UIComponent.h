#pragma once

#include "UIModel.h"
#include "UIController.h"
#include "UIView.h"

#include <list>

using namespace std;

/*
* UIComponent
* Modeliza un componente de la interfaz grafica que se compone de tres elementos
* para la implementacion del modelo MVC.
*/
class UIComponent{
public:

	/* Constructor / Destructor */
	UIComponent(UIModel* model_, UIView* view_, list<UIController*> controllers_);
	~UIComponent();

	/*
	* parse
	* Parsea los eventos en los controllers
	*/
	void parse(ALLEGRO_EVENT* event);

	/*
	* draw
	* Redibuja el componente en la interfaz
	*/
	void draw(void);

	/* Getters */
	list<UIController*>& getController(void);
	UIModel* getModel(void);
	UIView* getView(void);

	/* Setters */
	void setModel(UIModel* newModel);
	void setView(UIView* newView);
	void appendController(UIController* newController);
	void removeController(UIController* thisController);
	void clearController(void);

private:
	list<UIController*> controllers;
	UIModel* model;
	UIView* view;
};
