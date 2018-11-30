#include "SimpleButtonView.h"

SimpleButtonView::
SimpleButtonView(WindowUI* interface_, UIModel* model_) : UIView(interface_, model_) {
	images.clear();
}

SimpleButtonView::
~SimpleButtonView() {}

void
SimpleButtonView::draw(void) {

	/*
	* Hago uso de los valores por defecto de las configs
	* de colores y fuentes de texto.
	*/
	TextUI* button = (TextUI*)model;

	if (model->getVisible()) {

		switch (button->getStatus()) {

		}
	}
}