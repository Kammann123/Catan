#include "../../CatanGame/Building.h"
#include "../AllegroUI/UIView.h"


#define ROAD_IMAGE				"CatanGui\\GUIDesigns\\GameMenu\\buildings\\raod.png"
#define SETTLEMENT_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\settlement.png"
#define CITY_IMAGE				"CatanGui\\GUIDesigns\\GameMenu\\buildings\\city.png"

class BuildingView : public UIView
{
public:
	BuildingView(Building* model_ = nullptr);
	~BuildingView();
	void draw(void);
	void updateModelValues(void);
};