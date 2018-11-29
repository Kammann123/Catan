#include "MouseController.h"

MouseController::
MouseController(MouseDecorator* decorator) : UIController(decorator) {}

MouseController::
~MouseController() {}

void
MouseController::parse(ALLEGRO_EVENT* event) {

	/*
	* Obtengo el estado actual del FrameUI decorado
	* y reviso si me es de interes para el mouse
	*/
	MouseDecorator* decorator = (MouseDecorator*)getModel();
	FrameUI* frame = (FrameUI*)decorator->getModel();

	switch (frame->getStatus()) {

		case FrameUI::Status::IDLE:
			if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
				if (frame->isInside(event->mouse.x, event->mouse.y)) {
					frame->setStatus(FrameUI::Status::FOCUSED);
					decorator->focus();
				}
			}
			break;

		case FrameUI::Status::FOCUSED:
			if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
				if (!frame->isInside(event->mouse.x, event->mouse.y)) {
					frame->setStatus(FrameUI::Status::IDLE);
					decorator->exit();
				}
			}
			else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				frame->setStatus(FrameUI::Status::SELECTED);
				decorator->click();
			}
			break;

		case FrameUI::Status::SELECTED:
			if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
				if (decorator->getEnableDrag()) {
					frame->setStatus(FrameUI::Status::DRAGGED);
					frame->addPosition(event->mouse.dx, event->mouse.dy);
					decorator->drag();
				}
				else {
					if (!frame->isInside(event->mouse.x, event->mouse.y)) {
						frame->setStatus(FrameUI::Status::IDLE);
						decorator->exit();
					}
				}
			}
			else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				frame->setStatus(FrameUI::Status::FOCUSED);
				decorator->release();
			}
			break;

		case FrameUI::Status::DRAGGED:
			if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
				frame->addPosition(event->mouse.dx, event->mouse.dy);
				decorator->drag();
			}
			else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (!frame->isInside(event->mouse.x, event->mouse.y)) {
					frame->setStatus(FrameUI::Status::IDLE);
					decorator->exit();
				}
				else {
					frame->setStatus(FrameUI::Status::FOCUSED);
					decorator->drop();
				}
			}
			else {
				if (!frame->isInside(event->mouse.x, event->mouse.y)) {
					frame->setStatus(FrameUI::Status::IDLE);
					decorator->exit();
				}
			}
			break;
	}
}