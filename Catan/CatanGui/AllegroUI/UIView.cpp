#include "UIView.h"
#include "WindowUI.h"

UIView::
UIView(WindowUI* interface_, UIModel* model_) : interface(interface_), model(model_) {}

UIView::
~UIView() {}

void
UIView::update(void) {
	this->interface->draw();
}

