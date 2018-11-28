#include "Widgets.h"

SelectionFeature::
SelectionFeature(ALLEGRO_BITMAP* selectedBitmap_, ALLEGRO_BITMAP* focusedBitmap_, callback doIfSelected_, callback doIfFocused_)
{
	selectedBitmap = selectedBitmap_;
	focusedBitmap = focusedBitmap_;
	doIfSelected = doIfSelected_;
	doIfFocused = doIfFocused_;
	selected = false;
	focused = false;
}

SelectionFeature::
~SelectionFeature()
{
	// Destrucción de Bitmaps?
}

void SelectionFeature::
toggleSelection(void)
{
	selected = !selected;
}

void SelectionFeature::
setFocus(bool newState)
{
	this->focused = newState;
}

void SelectionFeature::
setSelectedBmap(ALLEGRO_BITMAP * newBitmap)
{
	selectedBitmap = newBitmap;
}

void SelectionFeature::
setFocusedBitmap(ALLEGRO_BITMAP * newBitmap)
{
	focusedBitmap = newBitmap;
}

bool SelectionFeature::
isSelected(void)
{
	return selected;
}

bool SelectionFeature::
isFocused(void)
{
	return focused;
}

TextField::
TextField(pixel width_, pixel height_, ALLEGRO_FONT * font_, ALLEGRO_COLOR boxColor_, callback doIfEnter_)
{
	height = height_;
	width = width_;
	text = "";
	boxColor = boxColor_;
	font = font_;
	selected = false;
	doIfEnter = doIfEnter_;

}

TextField::
~TextField()
{
}

void TextField::addChar(unsigned char newChar)
{
	text += newChar;
}

void TextField::
deleteChar(void)
{
	if (!text.empty())
	{
		text.pop_back();
	}
}

void TextField::
eraseAll(void)
{
	text.clear();
}

void TextField::
toggleSelection(void)
{
	selected = !selected;
}

void TextField::
clearSelection(void)
{
	selected = false;
}

bool TextField::
isSelected(void)
{
	return selected;
}

unsigned int TextField::
getWidth(void)
{
	return width;
}

unsigned int TextField::
getHeight(void)
{
	return height;
}

string TextField::
getText(void)
{
	return text;
}

ImageWidget::
ImageWidget(ALLEGRO_DISPLAY * display_, ALLEGRO_BITMAP * bitmap_, ImageCoords_t coords_)
{
	display = display_;
	coords = coords_;
	bitmap = bitmap_;

}

ImageWidget::
~ImageWidget()
{
}

ALLEGRO_BITMAP * ImageWidget::
getBitmap(void)
{
	return bitmap;
}

ALLEGRO_DISPLAY * ImageWidget::
getDisplay(void)
{
	return display;
}

ImageCoords_t ImageWidget::
getCoords(void)
{
	return coords;
}

void ImageWidget::
setBitmap(ALLEGRO_BITMAP * newBitmap)
{
	bitmap = newBitmap;
}

void ImageWidget::
setDisplay(ALLEGRO_DISPLAY * newDisplay)
{
	display = newDisplay;
}

void ImageWidget::
setCoords(ImageCoords_t newCoords)
{
	coords = newCoords;
}

void ImageWidget::
setCoords(double x, double y)
{
	this->coords.x = x;
	this->coords.y = y;
}

Label::Label(ALLEGRO_FONT * font_, string initialText)
{
	text = initialText;
	font = font_;
}

Label::~Label()
{
}

void Label::eraseAll(void)
{
	text = "";
}

void Label::setText(string text_)
{
	text = text_;
}

string Label::getText(void)
{
	return text;
}

unsigned int FrameUI::
getWidth(void)
{
	return width;
}

unsigned int FrameUI::getHeigth(void)
{
	return height;
}

ImageCoords_t FrameUI::
getCoords(void)
{
	return coords;
}

FrameState FrameUI::getState(void)
{
	return currentState;
}

callback FrameUI::
getOnClickCallback(void)
{
	return onClick;
}

callback FrameUI::
getOnExitCallback(void)
{
	return onExit;
}

callback FrameUI::getOnReleaseCallback(void)
{
	return onRelease;
}

callback FrameUI::
getOnEnterCallback(void)
{
	return onEnter;
}

void FrameUI::
setWidth(unsigned int newWidth)
{
	width = newWidth;
}

void FrameUI::
setHeight(unsigned int newHeigth)
{
	height = newHeigth;
}

void FrameUI::
setCoords(ImageCoords_t newCoords)
{
	coords = newCoords;
}

void FrameUI::
setXCoord(unsigned int newX)
{
	coords.x = newX;
}

void FrameUI::
setYCoord(unsigned int newY)
{
	coords.y = newY;
}

void FrameUI::
setState(FrameState newState)
{
	currentState = newState;
}

void FrameUI::
setOnClickCallback(callback newCallback)
{
	onClick = newCallback;
}

void FrameUI::
setOnEnterCallback(callback newCallback)
{
	onEnter = newCallback;
}

void FrameUI::
setOnExitCallback(callback newCallback)
{
	onExit = newCallback;
}

void FrameUI::
setOnReleaseCallback(callback newCallback)
{
	onRelease = newCallback;
}

void FrameUIController::
parseMouseEvent(ALLEGRO_EVENT * ev_)
{

}

void FrameUIController::
parseKeyboardEvent(ALLEGRO_EVENT * ev_)
{
	
}
