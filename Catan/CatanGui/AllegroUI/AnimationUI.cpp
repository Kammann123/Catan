#include "AnimationUI.h"

AnimationUI::
AnimationUI(string id, unsigned int frameQty) : MouseUI(id, 0, 0) {
	this->frameQty = frameQty;
	this->frameCounter = 0;
	this->timesToLoop = 1;
	this->loopCounter = 0;
	this->scaleTimer = 1;
	this->timeCounter = 0;
	this->activated = false;
	this->mode = Mode::DO_ONCE;
}

bool
AnimationUI::tick(void) {

	/* Aumenta el contador de timer para la escala del mismo
	* segun la base generada por la ventana a la que pertenece el modelo
	* y luego se determina si movio un frame
	*/
	timeCounter++;
	if (timeCounter >= scaleTimer) {
		timeCounter = 0;
		frameCounter++;
		if (frameCounter >= frameQty) {
			frameCounter = 0;
			if (mode == Mode::DO_ONCE) {
				stop();
			}
			else if (mode == Mode::X_TIMES) {
				loopCounter++;
				if (loopCounter >= timesToLoop) {
					loopCounter = 0;
					stop();
				}
			}
		}
		notifyObservers();
		return true;
	}

	/* No hubo cambio alguno de frame */
	return false;
}

void
AnimationUI::restart(void) {
	this->frameCounter = 0;
	this->loopCounter = 0;
	this->timeCounter = 0;
}

void
AnimationUI::start(void) {
	if (getEnable()) {
		this->activated = true;
		this->frameCounter = 0;
		this->loopCounter = 0;
		this->timeCounter = 0;
	}
}

void
AnimationUI::stop(void) {
	this->activated = false;
}

unsigned int
AnimationUI::getFrameCounter(void) const {
	return frameCounter;
}

unsigned int
AnimationUI::getTimeCounter(void) const {
	return timeCounter;
}

unsigned int
AnimationUI::getLoopCounter(void) const {
	return loopCounter;
}

unsigned int
AnimationUI::getScaleTimer(void) const {
	return scaleTimer;
}

unsigned int
AnimationUI::getLoopTimes(void) const {
	return timesToLoop;
}

unsigned int
AnimationUI::getFrameQty(void) const {
	return frameQty;
}

bool
AnimationUI::isActivated(void) const {
	return activated;
}

AnimationUI::Mode
AnimationUI::getMode(void) const {
	return mode;
}

void
AnimationUI::setMode(Mode mode) {
	this->mode = mode;
}

void
AnimationUI::setLoopTimes(unsigned int timesToLoop) {
	this->timesToLoop = timesToLoop;
}

void
AnimationUI::setScaleTimer(unsigned int scaleTimer) {
	this->scaleTimer = scaleTimer;
}

void
AnimationUI::setFrameQty(unsigned int frameQty) {
	this->frameQty = frameQty;
}

void 
AnimationUI::setFrameAction(Action frameAction_)
{
	frameAction = frameAction_;
}

void
AnimationUI::setLoopEndAction(Action loopEndAction_) {
	loopEndAction = loopEndAction_;
}

void 
AnimationUI::setAnimationEndAction(Action animationEndAction_)
{
	animationEndAction = animationEndAction_;
}

void 
AnimationUI::executeFrameAction(void * data)
{
	if (frameAction)
		frameAction(data);
}

void
AnimationUI::executeLoopEndAction(void* data) {
	if (loopEndAction)
		loopEndAction(data);
}

void 
AnimationUI::executeAnimationEndAction(void * data)
{
	if (animationEndAction)
		animationEndAction(data);
}