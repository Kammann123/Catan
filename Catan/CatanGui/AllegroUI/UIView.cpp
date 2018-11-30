#include "UIView.h"
#include "WindowUI.h"



UIView::UIView(WindowUI * interface_, UIModel * model_)
{
	interface = interface_;
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