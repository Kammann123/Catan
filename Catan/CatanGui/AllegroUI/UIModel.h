#pragma once

#include "../../MVC/Subject.h"

#include <string>

using namespace std;

/*
* UIModel
* Modelizacion basica de un modelo como elemento de la interfaz grafica
* cuyos estados son genericos para todo tipo de elemento. Clase base para el desarrollo
* de componentes y elementos para implementarlos en una interfaz.
*/
class UIModel : public Subject {
public:
	
	/* UIModel
	* Se construye con un estado inicial no visible ni habilitado.
	*/
	UIModel(string id, bool UIDestroys = true);
	~UIModel(void);

	/*
	* refactor - Metodo para definir la refactorizacion de los modelos
	* si fuere que dependen de otros elementos o componentes, para garantizar
	* una forma de correccion de la informacion que los contienen.
	*/
	virtual void refactor(void);

	/*
	* Configuracion y lectura de los estados actuales del modelo
	* en cuestion.
	*/
	void setVisible(bool visibleStatus);
	void setEnable(bool enableStatus);
	void setUIDestroy(bool destroys);
	void setId(string id);

	bool shouldUIDestroy(void);
	bool getVisible(void);
	bool getEnable(void);
	string getId(void);

protected:
	bool UIDestroys;
	bool enable;
	bool visible;
	string id;
};