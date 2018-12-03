#include "DiceView.h"
#include <allegro5/allegro.h>

DiceView::DiceView(Dice * model_) : UIView(model_)
{
	images.clear();
	images.setConfig(0, DICE_0_IMG);
	images.setConfig(1, DICE_1_IMG);
	images.setConfig(2, DICE_2_IMG);
	images.setConfig(3, DICE_3_IMG);
	images.setConfig(4, DICE_4_IMG);
	images.setConfig(5, DICE_5_IMG);
	images.setConfig(6, DICE_6_IMG);
}

DiceView::~DiceView()
{
}

void DiceView::draw(void)
{
	//Hacer modelo del dado que herede de la animacion
	Dice* dice = (Dice*) model;
	ALLEGRO_BITMAP * btMap;
	if (images.has(dice->getValue())) {
		btMap = images[dice->getValue()].bitmap;
	}

	/*Dibujo la imagen*/
	if (btMap != nullptr)
		al_draw_bitmap(btMap, dice->xPos(), dice->yPos(), 0);
}

void DiceView::updateModelValues(void)
{
}
