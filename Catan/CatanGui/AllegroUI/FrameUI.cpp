#include "FrameUI.h"

FrameUI::
FrameUI(size_t width, size_t height, pos_t x, pos_t y, Status status) {
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->status = status;
}

FrameUI::
~FrameUI(void) {}

void
FrameUI::setPosition(pos_t x, pos_t y) {
	this->x = x;
	this->y = y;
}

void
FrameUI::setWidth(size_t width) {
	this->width = width;
}

void
FrameUI::setHeight(size_t height) {
	this->height = height;
}

void
FrameUI::setStatus(Status status) {
	this->status = status;
}

FrameUI::Status
FrameUI::getStatus(void) {
	return this->status;
}

size_t
FrameUI::getWidth(void) {
	return this->width;
}

size_t
FrameUI::getHeight(void) {
	return this->height;
}

pos_t
FrameUI::xPos(void) {
	return this->x;
}

pos_t
FrameUI::yPos(void) {
	return this->y;
}