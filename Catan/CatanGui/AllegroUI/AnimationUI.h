#pragma once

#include "MouseUI.h"

/*
* AnimationUI
*/
class AnimationUI : public MouseUI {
public:

	/* Mode - Modos de funcionamiento del AnimationUI */
	enum Mode : unsigned int { LOOP, DO_ONCE, X_TIMES };

	/*
	* AnimationUI - Se construye por defecto con un identificador del componente grafico, 
	* y la informacion de la animacion, no obstante, por defecto se encuentra en modo DO_ONE, 
	* mientras que para configurar de otra forma, debe usarse los metodos.
	*/
	AnimationUI(string id, unsigned int frameQty);

	/**************************************
	* Interfaz de control de la animacion
	**************************************/
	bool isActivated(void) const;
	void restart(void);
	void start(void);
	void stop(void);
	bool tick(void);

	/********************************************
	* Interfaz de acceso a la informacion actual
	* de la animacion, metodos GETTER 
	********************************************/
	unsigned int getFrameCounter(void) const;
	unsigned int getTimeCounter(void) const;
	unsigned int getLoopCounter(void) const;
	unsigned int getScaleTimer(void) const;
	unsigned int getLoopTimes(void) const;
	unsigned int getFrameQty(void) const;
	Mode getMode(void) const;

	/********************************************
	* Interfaz de configuracion de la animacion
	* definiendo los parametros de la misma,
	* metodos SETTER
	********************************************/
	void setLoopTimes(unsigned int timesToLoop);
	void setScaleTimer(unsigned int scaleTimer);
	void setFrameQty(unsigned int frameQty);
	void setMode(Mode mode);

	/*****************************************
	* Interfaz de configuracion de CALLBACKS
	*****************************************/
	void setAnimationEndAction(Action animationEndAction_);
	void setLoopEndAction(Action loopEndAction_);
	void setFrameAction(Action frameAction_);

	/*************************************
	* Interfaz de ejecucion de CALLBACKS
	*************************************/
	void executeAnimationEndAction(void* data);
	void executeLoopEndAction(void* data);
	void executeFrameAction(void* data);

private:
	/* Valores de animacion */
	unsigned int frameQty;
	unsigned int frameCounter;
	unsigned int timesToLoop;
	unsigned int loopCounter;
	unsigned int scaleTimer;
	unsigned int timeCounter;

	/* Callbacks de ejecucion */
	Action frameAction;
	Action animationEndAction;
	Action loopEndAction;

	/* Flags */
	bool activated;
	Mode mode;
};