#include "../../AllegroUI/ChildWindowUI.h"

class DiscardWindow : public ChildWindowUI {
public:
	DiscardWindow(string id);

private:
	/***********************
	* Callbacks y acciones *
	***********************/
	void onClose(void* data);
	void onDiscard(void* data);
};