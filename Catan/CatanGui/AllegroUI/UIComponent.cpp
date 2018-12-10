#include "UIComponent.h"

UIComponent::
UIComponent(UIModel* model_, vector<UIView*> view_, vector<UIController*> controllers_){
	buffId = model_->getId();
	model = model_;
	views = view_;
	controllers = controllers_;
}

UIComponent::
UIComponent(string id) {
	buffId = id;
	model = nullptr;
	views = {};
	controllers = {};
}

UIComponent::
~UIComponent() {
	if (model) {
		if (model->shouldUIDestroy()) {
			delete model;
			model = nullptr;
		}
	}
	
	for (UIView* view : views) {
		if (view) {
			delete view;
			view = nullptr;
		}
	}
	
	for (UIController* controller : controllers) {
		if (controller) {
			delete controller;
			controller = nullptr;
		}
	}
}

void
UIComponent::refactor(void) {
	model->refactor();
	for (UIView* view : views) {
		view->refactor();
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

UIComponent*
UIComponent::operator[](string id) {
	string indexedId = getId() + "_" + id;

	for (UIComponent* component : components) {
		if (component->getId() == indexedId) {
			return component;
		}
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

void
UIComponent::attachComponent(UIComponent* component) {

	/* Primero verifico que exista algun model container.
	* En su defecto, creo uno, en caso de haberlo, y que
	* no sea un model container ( pero si un model )
	* habra un error, pues hay uso incorrecto de framework.
	*/
	if (model == nullptr ) {
		model = new UIModelContainer(buffId);
	}

	/* Luego se agrega el componente al vecto de componentes
	* y posteriormente se configura el modelo como un submodelo
	* del mismo container.
	*/
	components.push_back(component);
	FrameUI* frameModel = (FrameUI*)component->getModel();
	((UIModelContainer*)model)->attachModel(frameModel, frameModel->xPos(), frameModel->yPos());
}

void
UIComponent::detachComponent(UIComponent* component) {
	/* Verifico que este en existencia dentro de los components
	*/
	vector<UIComponent*>::iterator it = find(components.begin(), components.end(), component);
	if (it != components.end()) {
		components.erase(it);
		((UIModelContainer*)model)->detachModel((FrameUI*)component->getModel());
	}
}

vector<UIComponent*>::iterator
UIComponent::begin(void) {
	return components.begin();
}

vector<UIComponent*>::iterator
UIComponent::end(void) {
	return components.end();
}