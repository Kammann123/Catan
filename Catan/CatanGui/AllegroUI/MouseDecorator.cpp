#include "MouseDecorator.h"

MouseDecorator::
MouseDecorator(FrameUI* frame, bool dragMode) {

	/*
	* Si no se configura con un puntero distinto
	* a nullptr, claramente hubo algun error que no tiene sentido
	* permitir que continue, levanto excepcion.
	*/
	if (frame) {
		this->frame = frame;
		this->enableDragging = dragMode;
	}
	else {
		throw exception("MouseDecorator - No se puede configurar sin un frame.");
	}
}

MouseDecorator::
~MouseDecorator(void) {}

void 
MouseDecorator::setFocusAction(Action focus) {
	this->onFocus = focus;
}

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
MouseDecorator::focus(void* data) {
	onFocus(data);
}

void
MouseDecorator::exit(void* data) {
	onExit(data);
}

void
MouseDecorator::click(void* data) {
	onClick(data);
}

void
MouseDecorator::release(void* data) {
	onRelease(data);
}

void
MouseDecorator::drag(void* data) {
	onDrag(data);
}

void
MouseDecorator::drop(void* data) {
	onDrop(data);
}

void
MouseDecorator::move(void* data) {
	onMove(data);
}

void
MouseDecorator::setEnableDrag(bool dragStatus) {
	this->enableDragging = dragStatus;
}