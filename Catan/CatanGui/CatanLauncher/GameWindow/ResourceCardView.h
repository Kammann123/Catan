#include "../../CatanGame/ResourceCard.h"
#include "../AllegroUI/UIView.h"



class ResourceCardView : public UIView
{
public:
	ResourceCardView(ResourceCard* model_ = nullptr);
	~ResourceCardView();
	void draw(void);
	void updateModelValues(void);
};