#include "../AllegroUI/UIView.h"
#include "../../CatanGame/Dice.h"


#define DICE_0_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_0.png"
#define DICE_1_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_1.png"
#define DICE_2_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_2.png"
#define DICE_3_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_3.png"
#define DICE_4_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_4.png"
#define DICE_5_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_5.png"
#define DICE_6_IMG				"CatanGui\\GUIDesigns\\GameMenu\\dices\\dice_6.png"


class DiceView : public UIView
{
public:
	DiceView(Dice* model_ = nullptr);
	~DiceView();
	void draw(void);
	void updateModelValues(void);
};