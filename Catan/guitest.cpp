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
	void onEnter(void* data);
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
	UIComponent* textBox = UIBuilder::createTextBox("boxOne", 50);

	/* Attacheo los componentes */
	this->attachComponent(textBox);

	/* Configuro los componentes */
	MODEL(textBox, TextUI*)->setPosition(200, 100);
	MODEL(textBox, TextUI*)->setEnterAction(bind(&MenuGui::onEnter, this, _1));

	/* Configuro el Window */
	this->setBackground(0, 0, 0);
	this->setCloseAction(bind(&MenuGui::onExit, this, _1));
}

void
MenuGui::onEnter(void* data) {
	string text = MODEL((*this)["boxOne"], TextUI*)->getText();
	cout << text << endl;
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