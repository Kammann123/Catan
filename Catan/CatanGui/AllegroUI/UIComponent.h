#pragma once

#include "UIModelContainer.h"
#include "UIController.h"
#include "UIModel.h""
#include "UIView.h"

#include <iterator>
#include <string>
#include <vector>

using namespace std;

/*
* UIComponent
* Modeliza un componente de la interfaz grafica que se compone de tres elementos
* para la imp	lementacion del modelo MVC.
*
* Nota: Al dia de la fecha se le agrega a los UIComponentes la capacidad de contener
* otros UIComponents con la interfaz propia para dicha capacidad, de forma tal
* que se puede concebir la creacion de componente de componentes para reaprovechar
* lo componentes ya construidos.
*/
class UIComponent{
public:

	/*
	* UIComponent
	* Se debe construir un component con sus parte, o bien por defecto, en cuyo caso
	* se lo crea por defecto sin ningun tipo de informacion, dejando abierto a su posterior
	* configuracion, en caso de usar esta opcion, el attachment de componentes automaticamente
	* crea, en caso de no tenerlo, un modelo container!
	*/
	UIComponent(UIModel* model_, vector<UIView*> view_, vector<UIController*> controllers_);
	UIComponent(string id);
	~UIComponent();

	/*****************************************
	* Interfaz principal del UIComponent 
	*
	* Estos metodos permiten trabajar
	* sobre el component, dibujandolo,
	* pasandole los eventos, y ademas,
	* realizando una redefinicion del mismo
	* a traves del refactor para actualizar
	* cambios estructurales en el componente
	* como la redefinicion de una images... 
	*****************************************/
	void parse(ALLEGRO_EVENT* event);
	void refactor(void);
	void draw(void);

	/******************************************************
	* Interfaz de acceso a la informacion del UIComponent
	*
	* Tener en cuenta que el acceso a algun View especifico
	* no tiene mayor referencia que el orden de adhesion
	* del mismo, pues no tienen identificacion alguna, 
	* ya que su definicion no es absoluta al framework,
	* sino relativa a su utilizacion.
	*
	* Se accede al sub-component, con su id relativo.
	* Ejemplo: InfoBox sera de id "infobox", pero sus components
	*	seran "title", "frame", "message".
	* Se guardan como "infobox_title" pero se acceden por aca
	* con "title". Lo primero es para evitar conflictos
	* de ambito dentro de la ventana.
	******************************************************/
	UIController* operator[](UIController::Id id);
	UIComponent* operator[](string id);
	UIView* operator[](unsigned int index);

	vector<UIController*>& getControllers(void);
	vector<UIView*> getView(void);
	UIModel* getModel(void);
	string getId(void);

	/*****************************************
	* Interfaz para configurar UIComponent's *
	*****************************************/
	void attachComponent(UIComponent* component);
	void detachComponent(UIComponent* component);
	vector<UIComponent*>::iterator begin(void);
	vector<UIComponent*>::iterator end(void);

	/*********************************
	* Interfaz para configurar Model 
	*********************************/
	void setModel(UIModel* newModel);

	/**********************************
	* Interfaz para configurar View's
	**********************************/
	void appendView(UIView* view);
	void removeView(UIView* view);
	void clearView(UIView* view);

	/****************************************
	* Interfaz para configurar Controllers's
	****************************************/
	void appendController(UIController* newController);
	void removeController(UIController* thisController);
	void clearController(void);

private:
	vector<UIController*> controllers;
	vector<UIComponent*> components;
	vector<UIView*> views;
	UIModel* model;
	string buffId;
};