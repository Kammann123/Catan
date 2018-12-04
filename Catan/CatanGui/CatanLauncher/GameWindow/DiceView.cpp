#include "DiceView.h"
#include <allegro5/allegro.h>

#define DICE_1_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_1.png"
#define DICE_2_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_2.png"
#define DICE_3_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_3.png"
#define DICE_4_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_4.png"
#define DICE_5_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_5.png"
#define DICE_6_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_6.png"

DiceView::DiceView(Dice * model_) : UIView(model_)
{
	/* Configuro las imagenes que usara la View */
	images.clear();
	images.setConfig(1, DICE_1_IMG);
	images.setConfig(2, DICE_2_IMG);
	images.setConfig(3, DICE_3_IMG);
	images.setConfig(4, DICE_4_IMG);
	images.setConfig(5, DICE_5_IMG);
	images.setConfig(6, DICE_6_IMG);

	updateModelValues();
}

void DiceView::draw(void)
{
	Dice* dice = (Dice*) model;
	ALLEGRO_BITMAP * btMap;
	if (images.has(dice->getValue())) {
		btMap = images[dice->getValue()].bitmap;
	}

	/*Dibujo la imagen*/
	if (btMap != nullptr)
		al_draw_bitmap(btMap, dice->xPos(), dice->yPos(), 0);
}

void DiceView::updateModelValues(void) {
	AnimationUI* animation = (AnimationUI*)model;

	animation->setWidth( al_get_bitmap_width(images[1].bitmap) );
	animation->setHeight( al_get_bitmap_height(images[1].bitmap) );
}