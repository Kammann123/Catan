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

	if (animation->getEnable() && animation->isActivated()) {
		/* Verifico que el tipo de eventos recibidos sean los de interes
		* para el modelo correspondiente, de animacion, por ende, eventos de timer
		*/
		if (event->type == ALLEGRO_EVENT_TIMER) {
			if (animation->tick()) {
				if (animation->getFrameCounter() == 0) {
					animation->executeAnimationEndAction(event);
				}
				else {
					animation->executeFrameAction(event);
				}
			}
		}
	}
}