#include "ImageView.h"

ImageView::
ImageView(FrameUI * model_) : UIView(model_)
{
	images.setConfig(IV_BITMAP, IV_DEFAULT_BITMAP);
}

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
		al_draw_bitmap(images[IV_BITMAP].bitmap, pointer->getX(), pointer->getY(), IV_NO_FLAGS);
	}
}
