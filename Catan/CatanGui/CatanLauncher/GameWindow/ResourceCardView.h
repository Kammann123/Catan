#include "../../CatanGame/ResourceCard.h"
#include "../AllegroUI/UIView.h"


#define FOREST_CARD_IMAGE	""
#define HILL_CARD_IMAGE		""
#define MOUNTAIN_CARD_IMAGE	""
#define	FIELD_CARD_IMAGE	""
#define	PASTURES_CARD_IMAGE	""
#define	DESERT_CARD_IMAGE	""
#define	CARD_BACK_IMAGE		""
#define	CARD_BACK_ID		"cardBack"

class ResourceCardView : public UIView
{
public:
	ResourceCardView(ResourceCard* model_ = nullptr);
	~ResourceCardView();
	void draw(void);
	void updateModelValues(void);
};