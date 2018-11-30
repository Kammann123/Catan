#include "UIView.h"
#include "WindowUI.h"

UIView::UIView(UIModel * model_)
{
	model = model_;
}

UIView::
~UIView() {}

void
UIView::update(void) {
	this->interface->draw();
}

ColorConfig&
UIView::setColors(void) {
	return colors;
}

TextConfig&
UIView::setFonts(void) {
	return fonts;
}

ImageConfig&
UIView::setImages(void) {
	return images;
}

void 
UIView::setWindow(WindowUI* interface_) {
	this->interface = interface_;
}

void 
UIView::clearWindow(void) {
	this->interface = nullptr;
}