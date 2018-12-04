#include "../../CatanGame/Building.h"
#include "../AllegroUI/UIView.h"



class BuildingView : public UIView
{
public:
	BuildingView(Building* model_ = nullptr);
	~BuildingView();
	void draw(void);
	void updateModelValues(void);
};