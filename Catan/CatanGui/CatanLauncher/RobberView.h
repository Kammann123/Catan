#include "../../CatanGame/Robber.h"
#include "../AllegroUI/UIView.h"


#define ROBBER_IDLE_IMG		"CatanGui\\GUIDesigns\\GameMenu\\robber\\idle_robber.png"
#define ROBBER_FOCUSED_IMG	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\focused_robber.png"
#define ROBBER_SELECTED_IMG	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\selected_robber.png"
#define ROBBER_DRAGGED_IMG	ROBBER_SELECTED_IMG

class RobberView : public UIView
{
public:
	RobberView(Robber* model_ = nullptr);
	~RobberView();
	void draw(void);
	void updateModelValues(void);
};