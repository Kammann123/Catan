#include "UIView.h"
#include "WindowUI.h"

UIView::UIView(UIModel * model_)
{
	model = model_;
}

UIView::UIView() {}

UIView::
~UIView() {}

void
UIView::update(void) {
	if( interface )
		this->interface->draw();
}

ColorConfig&
UIView::getColors(void) {
	return colors;
}

TextConfig&
UIView::getFonts(void) {
	return fonts;
}

ImageConfig&
UIView::getImages(void) {
	return images;
}

SoundConfig&
UIView::getSamples(void) {
	return samples;
}

void 
UIView::setWindow(WindowUI* interface_) {
	this->interface = interface_;
}

void 
UIView::clearWindow(void) {
	this->interface = nullptr;
}

void
UIView::setModel(UIModel* model_) {
	this->model = model_;
}