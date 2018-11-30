#include "CatanGui/AllegroUI/WindowUI.h"
#include "CatanGui/AllegroWidgets/UIBuilder.h"

#include "CatanGui/AllegroUI/MouseUI.h"

#include <iostream>

using namespace std;

class MenuGui : public WindowUI {
public:
	MenuGui();
	void onExit(void* data);
	void onClick(void* data);
};

int main(int argc, char** argv) {

	WindowUI::InitAllegro();

	if (WindowUI::isAllegroInit()) {

		MenuGui myMenu;

		myMenu.start();

		while (myMenu.isOpen()) {

			myMenu.run();
		}
	}
	else {

		cout << "No pudo iniciar Allegro. Mal ahi." << endl;
	}
}

MenuGui::MenuGui() : WindowUI(400, 500) {
	/* Creamos los componentes */
	UIComponent* myButton = UIBuilder::createSimpleButton("button", "Conectar", 40);

	/* Attacheo los componentes */
	this->attachComponent(myButton);

	/* Configuro los componentes */
	MODEL(myButton, MouseUI*)->setPosition(50, 50);
	MODEL(myButton, MouseUI*)->setClickAction( bind(&MenuGui::onClick, this, _1) );

	/* Configuro el Window */
	this->setBackground(255, 255, 255);
	this->setCloseAction(bind(&MenuGui::onExit, this, _1));
}

void
MenuGui::onExit(void* data) {
	cout << "SALIENDO!!" << endl;
	getchar();
}

void
MenuGui::onClick(void* data) {
	cout << "APRETO WAAA!!" << endl;
}