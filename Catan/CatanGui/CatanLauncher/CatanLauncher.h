#pragma once

#include "CatanContext.h"

/*
* CatanLauncher
* Lanzador del juego de Catan, maneja los diferentes estados 
* y crea la informacion de contexto de los mismo, considerando que
* entre todos se propaga cierta informacion compartida, siendo
* lo que intercambian los objetos.
*/
class CatanLauncher {
public:

	/*
	* States - Estados o etapas del launcher.
	*/

private:

	CatanContext context;
};