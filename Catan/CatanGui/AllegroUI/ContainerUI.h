#pragma once

#include "FrameUI.h"

#include <map>
#include <string>

using namespace std;

/*
* Definicion del tipo caracteristico de Container para los
* componentes o elementos ordenados.
*
* - Las coordenadas x,y son utilizadas para referencias relativamente
* los objetos ordenados
*
* - La info permite definir alguna caracteristica adicional 
*/
typedef struct {
	double x;
	double y;
	double info;
}container_t;

/*
* ContainerUI
* Clase ContainerUI, modelizacion de un container en la interfaz que 
* define una zona de la ventana en la cual se pueden ordenar diferentes
* elementos.
*/
class ContainerUI : public FrameUI {
public:
	/*
	* ContainerUI - Se construye con el id representativo del container
	* junto con un determinado tamaño. Toda informacion adicional
	* se puede configurar posteriormente.
	*/
	ContainerUI(string id, size_t width, size_t height);

	/*
	* has - Permive ver si existe un elemento de dicho indice
	* dentro del mapa de elementos ordenados en el container.
	*/
	bool has(unsigned int index);
	bool has(string index);

	/*
	* operator[] - Permite acceder directamente al elemento con ese
	* id dentro del container, en caso de no existir, se levanta
	* una excepcion. Para evitar caer en este caso ver metodo has.
	*/
	container_t operator[](unsigned int index);
	container_t operator[](string index);

	/*
	* set - Permite configurar un nuevo elemento a ordenar
	* dentro del container, en caso de ya existir alguno
	* con ese indice, se lo reemplaza por el nuevo.
	*/
	void set(unsigned int index, double x, double y, double info);
	void set(string index, double x, double y, double info);

	/*
	* remove - Permite quitar un elmento ordenado dentro del container
	*/
	void remove(unsigned int index);
	void remove(string index);

private:
	map<unsigned int, container_t> iCont;
	map<string, container_t> sCont;
};