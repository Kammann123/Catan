#pragma once

#include "MouseUI.h"

/*
* AnimationUI
*/
class AnimationUI : public MouseUI {
public:

	/*Mode - Modos de funcionamiento del AnimationUI*/
	enum Mode : unsigned int { LOOP, DO_ONCE, X_TIMES };

	/*
	* AnimationUI
	*/
	AnimationUI(Mode mode_, int timesToLoop, string id, size_t width, size_t height, bool dragMode = false, bool holdMode = false);
	AnimationUI(int64_t maxTimerCount, Mode mode_, string id, size_t width, size_t height, bool dragMode = false, bool holdMode = false, int timesToLoop = 0);
	~AnimationUI();

	/*Incremento del count*/
	void incCount(void * data);

	/* Getters y setters*/
	unsigned int getFrameCount(void);
	int64_t getTimerCount(void);
	int64_t getMaxTimerCount(void);
	void setMaxTimerCount(int64_t maxTimerCount);
	bool getActivated(void);
	void setActivated(bool activated);
	Mode getMode(void);

	/* Configuracion de callbacks*/
	void setFrameAction(Action frameAction_);
	void setAnimationEndAction(Action animationEndAction_);
	/* Ejecucion de callbacks */
	void executeFrameAction(void* data);
	void executeAnimationEndAction(void* data);

private:
	unsigned int frameCounter;
	unsigned int timesToLoop;
	/* Callbacks de ejecucion */
	Action frameAction;
	Action animationEndAction;
	/* Count del timer*/
	int64_t timerCount;
	int64_t maxTimerCount;
	/*Flags*/
	bool activated;
	Mode mode;
};