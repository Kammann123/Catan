#include "../../../CatanGame/LongestRoad.h"
#include "../../AllegroUI/UIView.h"

class LongestRoadView : public UIView{
public:
	LongestRoadView(LongestRoad* model_ = nullptr);
	void draw(void);
};