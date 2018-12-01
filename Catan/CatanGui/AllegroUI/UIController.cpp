#include "UIController.h"

UIController::
UIController(UIModel* model) {
	this->model = model;
}

UIController::
~UIController() {}

UIModel*
UIController::getModel(void) {
	return this->model;
}