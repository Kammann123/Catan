#include "../AllegroUI/UIView.h"
#include "../../CatanGame/Dice.h"




class DiceView : public UIView
{
public:
	DiceView(Dice* model_ = nullptr);
	~DiceView();
	void draw(void);
	void updateModelValues(void);
};