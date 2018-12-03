#include "AnimationUI.h"

AnimationUI::AnimationUI(Mode mode_, int timesToLoop)
{
	timerCount = 0;
	maxTimerCount = 0;
	activated = false;
	mode = mode_;
	this->timesToLoop = timesToLoop;
}

AnimationUI::AnimationUI(int64_t maxTimerCount, Mode mode_, int timesToLoop)
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
		if ((mode == X_TIMES) && (frameCounter = timesToLoop))
		{
			activated = false;
			execute_action(data);
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


void AnimationUI::setOnTimerAction(Action timerAction_)
{
	timerAction = timerAction_;
}

void AnimationUI::execute_action(void * data)
{
	if (timerAction)
		timerAction(data);
}
