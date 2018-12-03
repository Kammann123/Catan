#pragma once

#include "MouseUI.h"

/*Mode - Modos de funcionamiento del AnimationUI*/
enum Mode : unsigned int { LOOP, DO_ONCE, X_TIMES };
/*

* AnimationUI
*/
class AnimationUI : public MouseUI {
public:
	/*
	* AnimationUI
	*/
	AnimationUI(Mode mode_, int timesToLoop = 0);
	AnimationUI(int64_t maxTimerCount, Mode mode_, int timesToLoop = 0);
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
	void setOnTimerAction(Action timerAction_);
	/* Ejecucion de callbacks */
	void execute_action(void* data);

private:
	unsigned int frameCounter;
	unsigned int timesToLoop;
	/* Callback de ejecucion */
	Action timerAction;
	/* Count del timer*/
	int64_t timerCount;
	int64_t maxTimerCount;
	/*Flags*/
	bool activated;
	Mode mode;
};