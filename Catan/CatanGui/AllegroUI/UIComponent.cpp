#include "UIComponent.h"

UIComponent::
UIComponent(UIModel * model_)
{
	model = model_;
}

UIComponent::
~UIComponent() {}

void
UIComponent::parse(ALLEGRO_EVENT* event) {
	for (UIController* controller : controllers) {
		if (this->model->getEnable()) {
			controller->parse(event);
		}
	}
}

void
UIComponent::draw(void) {
	if (this->model->getVisible()) {
		view->draw();
	}
}

list<UIController*>& UIComponent::
getController(void)
{
	return controllers;
}

UIModel * UIComponent::
getModel(void)
{
	return model;
}

UIView * UIComponent::getView(void)
{
	return view;
}

void UIComponent::
setModel(UIModel * newModel)
{
	model = newModel;
}

void UIComponent::
setView(UIView * newView)
{
	view = newView;
}

void UIComponent::
appendController(UIController * newController)
{
	controllers.push_back(newController);
}

void UIComponent::
removeController(UIController* thisController)
{
	this->controllers.remove(thisController);
}

void UIComponent::
clearController(void)
{
	this->controllers.clear();
}
