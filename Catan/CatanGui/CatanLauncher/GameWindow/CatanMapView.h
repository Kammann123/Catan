#include "../../../CatanGame/CatanMap.h"
#include "../../AllegroUI/UIView.h"

class CatanMapView : public UIView{
public:
	CatanMapView(CatanMap* model_ = nullptr);
	void draw(void);
};