#include "MouseController.h"

MouseController::
MouseController(MouseUI* frame) : UIController(frame, UIController::Id::MOUSE) {}

MouseController::
~MouseController() {}

void
MouseController::parse(ALLEGRO_EVENT* event) {

	/*
	* Obtengo el estado actual del MouseUI decorado
	* y reviso si me es de interes para el mouse
	*/
	MouseUI* frame = (MouseUI*)model;

	/*
	* Verifico que este habilitado el controller y su modelo
	*/
	if (getEnable() && frame->getEnable()) {

		switch (frame->getStatus()) {

			case MouseUI::Status::IDLE:
				if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
					if (frame->isInside(event->mouse.x, event->mouse.y)) {
						frame->setStatus(MouseUI::Status::FOCUSED);
						frame->focus(event);
					}
				}
				break;

			case MouseUI::Status::FOCUSED:
				if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
					if (!frame->isInside(event->mouse.x, event->mouse.y)) {
						frame->setStatus(MouseUI::Status::IDLE);
						frame->exit(event);
					}
				}
				else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					frame->setStatus(MouseUI::Status::SELECTED);
					frame->click(event);
				}
				break;

			case MouseUI::Status::SELECTED:
				if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
					if (frame->getEnableDrag()) {
						if (!frame->isInside(event->mouse.x, event->mouse.y)) {
							frame->setStatus(MouseUI::Status::IDLE);
							frame->exit(event);
						}
						else {
							frame->setStatus(MouseUI::Status::DRAGGED);
							frame->addPosition(event->mouse.dx, event->mouse.dy);
							frame->drag(event);
						}
					}
					else {
						if (!frame->isInside(event->mouse.x, event->mouse.y)) {
							frame->setStatus(MouseUI::Status::IDLE);
							frame->exit(event);
						}
					}
				}
				else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
					if (frame->getEnableHold()) {
						frame->setStatus(MouseUI::Status::HOLDING);
					}
					else {
						frame->setStatus(MouseUI::Status::FOCUSED);
						frame->release(event);
					}
				}
				break;

			case MouseUI::Status::HOLDING:
				if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					frame->setStatus(MouseUI::Status::FOCUSED);
					frame->focus(event);
				}
				break;

			case MouseUI::Status::DRAGGED:
				if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
					frame->addPosition(event->mouse.dx, event->mouse.dy);
					frame->drag(event);
				}
				else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
					if (!frame->isInside(event->mouse.x, event->mouse.y)) {
						frame->setStatus(MouseUI::Status::IDLE);
						frame->exit(event);
					}
					else {
						frame->setStatus(MouseUI::Status::FOCUSED);
						frame->drop(event);
					}
				}
				break;
		}
	}
}