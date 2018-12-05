#include "../../../CatanGame/Player.h"
#include "../../AllegroUI/UIView.h"

class PlayerView : public UIView{
public:
	PlayerView(Player* model_ = nullptr);
	void draw(void);
};