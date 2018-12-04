#include "../../AllegroUI/UIView.h"
#include "../../../CatanGame/Dice.h"

class DiceView : public UIView{
public:
	DiceView(Dice* model_ = nullptr);
	void draw(void);
	void refactor(void);
};