#include "MouseUI.h"

MouseUI::
MouseUI(string id, size_t width, size_t height, bool dragMode, bool holdMode) : FrameUI(id, width, height) {
	this->enableDragging = dragMode;
	this->enableHold = holdMode;
}

MouseUI::
~MouseUI(void) {}

void
MouseUI::clear(void) {
	this->status = Status::IDLE;
}

void 
MouseUI::setEnable(bool enableStatus) {
	if (enableStatus == false) {
		clear();
	}
	this->enable = enableStatus;
}

void
MouseUI::setFocusAction(Action focus) {
	this->onFocus = focus;
}

void
MouseUI::setExitAction(Action exit) {
	this->onExit = exit;
}

void
MouseUI::setClickAction(Action click) {
	this->onClick = click;
}

void
MouseUI::setReleaseAction(Action release) {
	this->onRelease = release;
}

void
MouseUI::setDragAction(Action drag) {
	this->onDrag = drag;
}

void
MouseUI::setDropAction(Action drop) {
	this->onDrop = drop;
}

void
MouseUI::setMoveAction(Action move) {
	this->onMove = move;
}

void
MouseUI::focus(void* data) {
	if (onFocus) onFocus(data);
}

void
MouseUI::exit(void* data) {
	if (onExit)	onExit(data);
}

void
MouseUI::click(void* data) {
	if (onClick)	onClick(data);
}

void
MouseUI::release(void* data) {
	if (onRelease)	onRelease(data);
}

void
MouseUI::drag(void* data) {
	if (onDrag)	onDrag(data);
}

void
MouseUI::drop(void* data) {
	if (onDrop)	onDrop(data);
}

void
MouseUI::move(void* data) {
	if (onMove)	onMove(data);
}

void
MouseUI::setEnableDrag(bool dragStatus) {
	this->enableDragging = dragStatus;
}

bool
MouseUI::getEnableDrag(void) {
	return this->enableDragging;
}

void
MouseUI::setStatus(Status status) {
	this->status = status;
	notifyObservers();
}

MouseUI::Status
MouseUI::getStatus(void) {
	return this->status;
}

void
MouseUI::setEnableHold(bool holdStatus) {
	this->enableHold = holdStatus;
}

bool
MouseUI::getEnableHold(void) {
	return enableHold;
}