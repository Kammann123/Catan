#pragma once

#include "FrameUI.h"

#include <map>
#include <list>

using namespace std;

typedef struct {
	double x;
	double y;
}relative_t;

/*
* UIModelContainer - Permite contener varios models
* para la confeccion de Componentes en conjunto
*/
class UIModelContainer : public FrameUI {
public:
	/*
	* UIModelContainer - Se construye con un id que lo identifica
	* dentro de los modelos o componentes en la interfaz
	*/
	UIModelContainer(string id);
	~UIModelContainer(void);

	/*********************************************
	* Interfaz redefinida para todos los modelos *
	*********************************************/
	virtual void setPosition(pos_t x, pos_t y);
	virtual void addPosition(pos_t x, pos_t y);
	virtual void setVisible(bool visibleStatus);
	virtual void setEnable(bool enableStatus);
	virtual void setUIDestroy(bool destroys);
	virtual void refactor(void);

	/*********************************
	* Interfaz para manejo de models *
	*********************************/
	void attachModel(FrameUI* model, double x, double y);
	void detachModel(FrameUI* model);
	list<FrameUI*> getModels(void);

private:
	map<FrameUI*, relative_t> models;
};