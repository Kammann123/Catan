#include "UIDecorator.h"

UIDecorator::
UIDecorator(UIModel* model) {
	this->model = model;
}

UIDecorator::
~UIDecorator(void) {}

UIModel*
UIDecorator::getModel(void) {
	return this->model;
}

bool 
UIDecorator::attach(Observer* observer) {
	return this->model->attach(observer);
}

bool
UIDecorator::detach(Observer* observer) {
	return this->model->detach(observer);
}