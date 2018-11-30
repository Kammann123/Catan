#include "MouseUI.h"

MouseUI::
MouseUI(string id, bool dragMode) : FrameUI(id) {
	this->enableDragging = dragMode;
}

MouseUI::
~MouseUI(void) {}

void
MouseUI::setFocusAction(Action focus) {
	this->onFocus = focus;
}

void
MouseUI::setExitACtion(Action exit) {
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