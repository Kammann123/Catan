#include "MouseDecorator.h"

MouseDecorator::
MouseDecorator(FrameUI* frame, bool dragMode) : UIDecorator(frame) {
	this->enableDragging = dragMode;
}

MouseDecorator::
~MouseDecorator(void) {}

void
MouseDecorator::setExitACtion(Action exit) {
	this->onExit = exit;
}

void
MouseDecorator::setClickAction(Action click) {
	this->onClick = click;
}

void
MouseDecorator::setReleaseAction(Action release) {
	this->onRelease = release;
}

void
MouseDecorator::setDragAction(Action drag) {
	this->onDrag = drag;
}

void
MouseDecorator::setDropAction(Action drop) {
	this->onDrop = drop;
}

void
MouseDecorator::setMoveAction(Action move) {
	this->onMove = move;
}

void
MouseDecorator::focus(void) {
	if(onFocus) onFocus();
}

void
MouseDecorator::exit(void) {
	if(onExit)	onExit();
}

void
MouseDecorator::click(void) {
	if(onClick)	onClick();
}

void
MouseDecorator::release(void) {
	if(onRelease)	onRelease();
}

void
MouseDecorator::drag(void) {
	if(onDrag)	onDrag();
}

void
MouseDecorator::drop(void) {
	if(onDrop)	onDrop();
}

void
MouseDecorator::move(void) {
	if(onMove)	onMove();
}

void
MouseDecorator::setEnableDrag(bool dragStatus) {
	this->enableDragging = dragStatus;
}

bool
MouseDecorator::getEnableDrag(void) {
	return this->enableDragging;
}