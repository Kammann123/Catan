#include "../../../CatanGame/Building.h"
#include "../../AllegroUI/UIView.h"

class BuildingView : public UIView{
public:
	BuildingView(Building* model_ = nullptr);
	void draw(void);
	void refactor(void);
};