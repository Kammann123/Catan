#include "MultiLabelView.h"

MultiLabelView::
MultiLabelView(TextUI* model_) : UIView(model_){
	colors.setConfig(MLA_TEXT_COLOR, MLA_DEFAULT_TEXT_COLOR);
	fonts.setConfig(MLA_FONT, MLA_DEFAULT_FONT, MLA_DEFAULT_FONT_SIZE);

	this->width = width;
	this->height = height;
}

void 
MultiLabelView::setWidth(double width) {
	this->width = width;
}

void
MultiLabelView::setHeight(double height) {
	this->height = height;
}

void 
MultiLabelView::draw(void){
	if (model->getVisible()){
		TextUI* pointer = (TextUI*)model;
		al_draw_multiline_text(
			fonts[MLA_FONT].font,
			colors[MLA_TEXT_COLOR].color,
			pointer->xPos(),
			pointer->yPos(),
			width,
			height,
			ALLEGRO_ALIGN_LEFT,
			pointer->getText().c_str()
		);
	}
}