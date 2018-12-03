#include "../../CatanGame/ResourceCard.h"
#include "../AllegroUI/UIView.h"


#define FOREST_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\wood_card.png"
#define HILL_CARD_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\cards\\brick_card.png"
#define MOUNTAIN_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\ore_card.png"
#define	FIELD_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\wheat_card.png"
#define	PASTURES_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\wool_card.png"
#define	CARD_BACK_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\cards\\card_back.png"
#define	CARD_BACK_ID		"cardBack"

class ResourceCardView : public UIView
{
public:
	ResourceCardView(ResourceCard* model_ = nullptr);
	~ResourceCardView();
	void draw(void);
	void updateModelValues(void);
};