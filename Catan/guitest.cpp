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

MenuGui::MenuGui() : WindowUI(1000, 800) {
	/* Creamos los componentes */
	UIComponent* myButton = UIBuilder::createButton("button");
	UIComponent* myButtonOne = UIBuilder::createButton("buttonOne");

	/* Attacheo los componentes */
	this->attachComponent(myButton);
	this->attachComponent(myButtonOne);

	/* Configuro los componentes */
	MODEL(myButton, MouseUI*)->setPosition(200, 200);
	MODEL(myButton, MouseUI*)->setClickAction(bind(&MenuGui::onClick, this, _1));
	MODEL(myButtonOne, MouseUI*)->setPosition(200, 500);
	MODEL(myButtonOne, MouseUI*)->setClickAction(bind(&MenuGui::onClick, this, _1));

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