#include "UIComponent.h"

UIComponent::
UIComponent(UIModel* model_, vector<UIView*> view_, vector<UIController*> controllers_)
{
	model = model_;
	views = view_;
	controllers = controllers_;
}

UIComponent::
~UIComponent() {
	if (model) {
		if (model->shouldUIDestroy()) {
			delete model;
		}
	}
	
	for (UIView* view : views) {
		if (view)
			delete view;
	}
	
	for (UIController* controller : controllers) {
		if(controller)
			delete controller;
	}
}

void
UIComponent::parse(ALLEGRO_EVENT* event) {
	if (this->model->getEnable()) {
		for (UIController* controller : controllers) {
			controller->parse(event);
		}
	}
}

void
UIComponent::draw(void) {
	if (this->model->getVisible()) {
		for (UIView* view : views) {
			view->draw();
		}
	}
}

UIController*
UIComponent::operator[](UIController::Id id) {
	for (UIController* controller : controllers) {
		if (controller->getId() == id) {
			return controller;
		}
	}
	return nullptr;
}

UIView*
UIComponent::operator[](unsigned int index) {
	if (index < views.size()) {
		return views[index];
	}
	return nullptr;
}

vector<UIController*>& UIComponent::
getControllers(void)
{
	return controllers;
}

UIModel * UIComponent::
getModel(void)
{
	return model;
}

vector<UIView *> UIComponent::getView(void)
{
	return views;
}

void UIComponent::
setModel(UIModel * newModel)
{
	model = newModel;
}

void
UIComponent::appendView(UIView* view) {
	views.push_back(view);
}

void 
UIComponent::removeView(UIView* view) {
	this->views.erase(find(views.begin(), views.end(), view));
}

void 
UIComponent::clearView(UIView* view) {
	for (UIView* view : views) {
		if (view) {
			delete view;
		}
	}
	views.clear();
}

void UIComponent::
appendController(UIController * newController)
{
	controllers.push_back(newController);
}

void UIComponent::
removeController(UIController* thisController)
{
	this->controllers.erase( find(controllers.begin(), controllers.end(), thisController) );
}

void UIComponent::
clearController(void)
{
	for (UIController* controller : controllers) {
		if (controller)
			delete controller;
	}
	this->controllers.clear();
}

string UIComponent::
getId(void)
{
	return this->model->getId();
}