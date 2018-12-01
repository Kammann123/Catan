#pragma once

#include "UIModel.h"
#include "UIController.h"
#include "UIView.h"

#include <vector>

using namespace std;

/*
* UIComponent
* Modeliza un componente de la interfaz grafica que se compone de tres elementos
* para la imp	lementacion del modelo MVC.
*/
class UIComponent{
public:

	/* Constructor / Destructor */
	UIComponent(UIModel* model_, vector<UIView*> view_, vector<UIController*> controllers_);
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
	vector<UIController*>& getController(void);
	vector<UIView*> getView(void);
	UIModel* getModel(void);
	string getId(void);

	/* Setters */
	void setModel(UIModel* newModel);

	void appendView(UIView* view);
	void removeView(UIView* view);
	void clearView(UIView* view);

	void appendController(UIController* newController);
	void removeController(UIController* thisController);
	void clearController(void);

private:
	vector<UIController*> controllers;
	vector<UIView*> views;
	UIModel* model;
};
