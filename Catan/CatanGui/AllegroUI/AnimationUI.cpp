#include "AnimationUI.h"

AnimationUI::AnimationUI(Mode mode_, int timesToLoop, string id, size_t width, size_t height, bool dragMode, bool holdMode): MouseUI(id, width, height, dragMode, holdMode)
{
	timerCount = 0;
	maxTimerCount = 0;
	activated = false;
	mode = mode_;
	this->timesToLoop = timesToLoop;
}

AnimationUI::AnimationUI(int64_t maxTimerCount, Mode mode_, string id, size_t width, size_t height, bool dragMode, bool holdMode, int timesToLoop): MouseUI(id, width, height, dragMode, holdMode)
{
	timerCount = 0;
	this->maxTimerCount = maxTimerCount;
	activated = false;
	mode = mode_;
	this->timesToLoop = timesToLoop;
}

AnimationUI::~AnimationUI()
{
}


void AnimationUI::incCount(void * data)
{
	timerCount++;
	if (timerCount == maxTimerCount)
	{
		timerCount = 0;
		frameCounter++;
		executeFrameAction(data);
		if ((mode == X_TIMES) && (frameCounter = timesToLoop))
		{
			activated = false;
			executeAnimationEndAction(data);
			frameCounter = 0;
		}
		notifyObservers();
	}
}

unsigned int AnimationUI::getFrameCount(void)
{
	return frameCounter;
}

int64_t AnimationUI::getTimerCount(void)
{
	return timerCount;
}

int64_t AnimationUI::getMaxTimerCount(void)
{
	return maxTimerCount;
}

void AnimationUI::setMaxTimerCount(int64_t maxTimerCount)
{
	this->maxTimerCount = maxTimerCount;
}

bool AnimationUI::getActivated(void)
{
	return activated;
}

void AnimationUI::setActivated(bool activated)
{
	this->activated = activated;
}

Mode AnimationUI::getMode(void)
{
	return mode;
}


void AnimationUI::setFrameAction(Action frameAction_)
{
	frameAction = frameAction_;
}

void AnimationUI::setAnimationEndAction(Action animationEndAction_)
{
	animationEndAction = animationEndAction_;
}

void AnimationUI::executeFrameAction(void * data)
{
	if (frameAction)
		frameAction(data);
}

void AnimationUI::executeAnimationEndAction(void * data)
{
	if (animationEndAction)
		animationEndAction(data);
}
