#include "ErrorWindow.h"
#include "../../AllegroWidgets/UIBuilder.h"

#define ERRORWINDOW_BACKGROUND "CatanGui\\GUIDesigns\\ErrorWindow\\background.png"

#define ERRORWINDOW_OK_NORMAL	"CatanGui\\GUIDesigns\\ErrorWindow\\button.png"
#define ERRORWINDOW_OK_FOCUS	"CatanGui\\GUIDesigns\\ErrorWindow\\button_focus.png"

ErrorWindow::
ErrorWindow(string id, CatanLauncher& _launcher) : ChildWindowUI(id, 550, 345), launcher(_launcher) {
	UIComponent* okButton = UIBuilder::createButton("button");

	/* Configuracion del boton */
	(*okButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, ERRORWINDOW_OK_NORMAL);
	(*okButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, ERRORWINDOW_OK_FOCUS);
	(*okButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, ERRORWINDOW_OK_FOCUS);

	/* Cargo los callbacks */
	MODEL(okButton, MouseUI*)->setClickAction(bind(&ErrorWindow::onOk, this, _1));

	/* Configuro las posiciones */
	MODEL(okButton, MouseUI*)->setPosition(180, 200);

	/* Agrego... */
	this->attachComponent(okButton);

	/* Configuraciones generales */
	this->setBackground(ERRORWINDOW_BACKGROUND);

	/* Habilito los componentes */
	this->visibleComponent("button", true);
	this->enableComponent("button", true);
}

void
ErrorWindow::onOk(void* data) {
	launcher.change(CatanLauncher::States::MAIN_MENU);
}