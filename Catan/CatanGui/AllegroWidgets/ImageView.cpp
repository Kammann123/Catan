#include "ImageView.h"

ImageView::
ImageView(FrameUI * model_) : UIView(model_)
{}

ImageView::
~ImageView()
{
}

void ImageView::
draw(void)
{
	if (model->getVisible())
	{
		FrameUI* pointer = (FrameUI*)model;
		if (images.has(IV_BITMAP)) {
			al_draw_bitmap(images[IV_BITMAP].bitmap, pointer->xPos(), pointer->yPos(), IV_NO_FLAGS);
		}
	}
}

void ImageView::
updateModelValues() 
{
	FrameUI* pointer = (FrameUI*)model;
	if (images.has(IV_BITMAP)) {
		pointer->setWidth(al_get_bitmap_width(images[IV_BITMAP].bitmap));
		pointer->setHeight(al_get_bitmap_height(images[IV_BITMAP].bitmap));
	}
}
