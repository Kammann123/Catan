#include "DiceView.h"
#include <allegro5/allegro.h>

#define DICE_1_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_1.png"
#define DICE_1_FOCUSED_IMG		"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_1_focused.png"
#define DICE_2_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_2.png"
#define DICE_2_FOCUSED_IMG		"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_2_focused.png"
#define DICE_3_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_3.png"
#define DICE_3_FOCUSED_IMG		"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_3_focused.png"
#define DICE_4_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_4.png"
#define DICE_4_FOCUSED_IMG		"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_4_focused.png"
#define DICE_5_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_5.png"
#define DICE_5_FOCUSED_IMG		"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_5_focused.png"
#define DICE_6_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_6.png"
#define DICE_6_FOCUSED_IMG		"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_6_focused.png"

DiceView::DiceView(Dice * model_) : UIView(model_)
{
	/* Configuro las imagenes que usara la View */
	images.clear();
	images.setConfig(1, DICE_1_IMG);
	images.setConfig("1_focused", DICE_1_FOCUSED_IMG);
	images.setConfig(2, DICE_2_IMG);
	images.setConfig("2_focused", DICE_2_FOCUSED_IMG);
	images.setConfig(3, DICE_3_IMG);
	images.setConfig("3_focused", DICE_3_FOCUSED_IMG);
	images.setConfig(4, DICE_4_IMG);
	images.setConfig("4_focused", DICE_4_FOCUSED_IMG);
	images.setConfig(5, DICE_5_IMG);
	images.setConfig("5_focused", DICE_5_FOCUSED_IMG);
	images.setConfig(6, DICE_6_IMG);
	images.setConfig("6_focused", DICE_6_FOCUSED_IMG);

	updateModelValues();
}

void DiceView::draw(void)
{
	Dice* dice = (Dice*) model;
	ALLEGRO_BITMAP * btMap = nullptr;
	if (dice->getStatus() == MouseUI::Status::FOCUSED) {
		string img = to_string(dice->getValue()) + "_focused";
		if (images.has(img)) {
			btMap = images[img].bitmap;
		}
	}
	else {
		if (images.has(dice->getValue())) {
			btMap = images[dice->getValue()].bitmap;
		}
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