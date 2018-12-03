#include "../../CatanGame/LongestRoad.h"
#include "../AllegroUI/UIView.h"


#define LONGEST_ROAD_IMG		"CatanGui\\GUIDesigns\\GameMenu\\longest_road.png"
#define LONGEST_ROAD_ID			"longest_road"

class LongestRoadView : public UIView
{
public:
	LongestRoadView(LongestRoad* model_ = nullptr);
	~LongestRoadView();
	void draw(void);
	void updateModelValues(void);
};