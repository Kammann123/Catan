#include "../../../CatanGame/Robber.h"
#include "../../AllegroUI/UIView.h"

class RobberView : public UIView{
public:
	RobberView(Robber* model_ = nullptr);
	void draw(void);
	void refactor(void);
};