#include "UIComponent.h"

UIComponent::
UIComponent(UIModel * model_)
{
	model = model_;
}

UIComponent::
~UIComponent()
{
}

list<UIController*>& UIComponent::
getController(void)
{
	return controller;
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
	controller.push_back(newController);
}

void UIComponent::
removeController(UIController* thisController)
{
	this->controller.remove(thisController);
}

void UIComponent::
clearController(void)
{
	this->controller.clear();
}
