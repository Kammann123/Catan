#include "../../CatanGame/Robber.h"
#include "../AllegroUI/UIView.h"



class RobberView : public UIView
{
public:
	RobberView(Robber* model_ = nullptr);
	~RobberView();
	void draw(void);
	void updateModelValues(void);
};