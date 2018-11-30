#pragma once
#include "../AllegroUI/FrameUI.h"
#include "../AllegroUI/UIView.h"

#define IV_BITMAP "bitmap"
#define IV_DEFAULT_BITMAP "IV_default_bitmap.png"
#define IV_NO_FLAGS 0

class ImageView : public UIView
{
public:
	ImageView(FrameUI* model_ = nullptr);
	~ImageView();
	void draw(void);
};