#include "AnimationController.h"

AnimationController::
AnimationController(AnimationUI* animationUI) : UIController(animationUI) {}

AnimationController::
~AnimationController(void) {}

void
AnimationController::parse(ALLEGRO_EVENT* event) {

	/*
	* Busco el modelo, verifico su estado de actividad
	* y luego parseo los eventos correspondientes
	*/
	AnimationUI* animation = (AnimationUI*)model;

	if (animation->getEnable()) {
		if (event->type == ALLEGRO_EVENT_TIMER) {
			animation->incCount(event);
		}
	}
}