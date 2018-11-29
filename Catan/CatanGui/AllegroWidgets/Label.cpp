#include "Label.h"


void
Label::setText(string newText) {
	this->text = newText;
}

Label::Label(size_t width, size_t height, pos_t x, pos_t y, Status status, string text) : FrameUI(width, height, x, y, status)
{
	this->text = text;
}

Label::~Label()
{
}

string
Label::getText() {
	return text;
}

