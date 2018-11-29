#pragma once

#include "../../MVC/Subject.h"

/*
* UIModel
* Modelizacion basica de un modelo como elemento de la interfaz grafica
* cuyos estados son genericos para todo tipo de elemento. Clase base para el desarrollo
* de componentes y elementos para implementarlos en una interfaz.
*/
class UIModel : public Subject {
public:

	/*
	* UIModel
	* Se construye con un estado inicial no visible ni habilitado.
	*/
	UIModel(void);
	~UIModel(void);

	/*
	* Configuracion y lectura de los estados actuales del modelo
	* en cuestion.
	*/
	void setVisible(bool visibleStatus);
	void setEnable(bool enableStatus);

	bool getVisible(void);
	bool getEnable(void);

private:
	bool enable;
	bool visible;
};