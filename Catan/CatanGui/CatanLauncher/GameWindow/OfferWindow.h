#include "../../AllegroUI/ChildWindowUI.h"

class OfferWindow : public ChildWindowUI {
public:
	OfferWindow(string id);

private:
	/***********************
	* Callbacks y acciones *
	***********************/
	void onClose(void* data);
	void onTrade(void* data);
};