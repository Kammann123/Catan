#include "MainMenu.h"
#include "../CatanLauncher.h"
#include "../../AllegroWidgets/UIBuilder.h"
#include "../../AllegroWidgets/ImageView.h"

#include <string>

using namespace std;

#define MAINMENU_MUSIC		"CatanGui\\Sounds\\catan.ogg"
#define MAINMENU_BACKGROUND	"CatanGui\\GUIDesigns\\MainMenu\\background.png"

#define MAINMENU_STATUS_CLOSED "CatanGui\\GUIDesigns\\MainMenu\\closed.png"
#define MAINMENU_STATUS_OFFLINE "CatanGui\\GUIDesigns\\MainMenu\\offline.png"
#define MAINMENU_STATUS_ONLINE "CatanGui\\GUIDesigns\\MainMenu\\online.png"
#define MAINMENU_STATUS_ERROR "CatanGui\\GUIDesigns\\MainMenu\\error.png"

#define MAINMENU_TEXTBOX_IDLE "CatanGui\\GUIDesigns\\MainMenu\\textbox_idle.png"
#define MAINMENU_TEXTBOX_SELECTED "CatanGui\\GUIDesigns\\MainMenu\\textbox_selected.png"

#define MAINMENU_CONNECT_IDLE "CatanGui\\GUIDesigns\\MainMenu\\connect_idle.png"
#define MAINMENU_CONNECT_FOCUS "CatanGui\\GUIDesigns\\MainMenu\\connect_focused.png"
#define MAINMENU_CONNECT_SELECTED "CatanGui\\GUIDesigns\\MainMenu\\connect_selected.png"

#define MAINMENU_CANCEL_IDLE	"CatanGui\\GUIDesigns\\MainMenu\\cancel_normal.png"
#define MAINMENU_CANCEL_FOCUS	"CatanGui\\GUIDesigns\\MainMenu\\cancel_focused.png"
#define MAINMENU_CANCEL_SELECTED	"CatanGui\\GUIDesigns\\MainMenu\\cancel_selected.png"

#define CONNECT_FOCUS_SOUND "CatanGui\\Sounds\\button_focus.wav"
#define CONNECT_SELECT_SOUND "CatanGui\\Sounds\\press.wav"

#define CANCEL_FOCUS_SOUND CONNECT_FOCUS_SOUND
#define CANCEL_SELECT_SOUND CONNECT_SELECT_SOUND

MainMenu::
MainMenu(CatanLauncher& _launcher) : WindowUI(1080, 640), launcher(_launcher) {
	prevState = CatanNetworking::States::CLOSED;

	/* Creo los componentes */
	UIComponent* nameBox = UIBuilder::createTextBox("name", 26, TextUI::Mode::LETTER);
	UIComponent* ipBox = UIBuilder::createTextBox("ip", 26, TextUI::Mode::EVERYTHING);
	UIComponent* portBox = UIBuilder::createTextBox("port", 25, TextUI::Mode::NUMBER);
	UIComponent* connectButton = UIBuilder::attachSample(UIBuilder::createButton("connect"));
	UIComponent* cancelButton = UIBuilder::attachSample(UIBuilder::createButton("cancel"));
	UIComponent* status = UIBuilder::createImage("status");
	UIComponent* message = UIBuilder::createLabel("message", 100);

	/* Configuro los labels */
	MODEL(message, TextUI*)->setText("[CatanGame]: Test!");

	/* Configuro las imagenes */
	(*status)[0]->getImages().setConfig(IV_BITMAP, MAINMENU_STATUS_CLOSED);

	/* Configuro los botones! */
	(*connectButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, MAINMENU_CONNECT_IDLE);
	(*connectButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, MAINMENU_CONNECT_FOCUS);
	(*connectButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, MAINMENU_CONNECT_SELECTED);
	(*connectButton)[0]->getImages().setConfig(MouseUI::Status::HOLDING, MAINMENU_CONNECT_SELECTED);
	(*connectButton)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, MAINMENU_CONNECT_SELECTED);

	(*connectButton)[1]->getSamples().setConfig(MouseUI::Status::SELECTED, CONNECT_SELECT_SOUND);
	(*connectButton)[1]->getSamples().setConfig(MouseUI::Status::FOCUSED, CONNECT_FOCUS_SOUND);

	MODEL(connectButton, MouseUI*)->setClickAction(bind(&MainMenu::onConnect, this, _1));

	(*cancelButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, MAINMENU_CANCEL_IDLE);
	(*cancelButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, MAINMENU_CANCEL_FOCUS);
	(*cancelButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, MAINMENU_CANCEL_SELECTED);
	(*cancelButton)[0]->getImages().setConfig(MouseUI::Status::HOLDING, MAINMENU_CANCEL_SELECTED);
	(*cancelButton)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, MAINMENU_CANCEL_SELECTED);

	(*cancelButton)[1]->getSamples().setConfig(MouseUI::Status::SELECTED, CANCEL_SELECT_SOUND);
	(*cancelButton)[1]->getSamples().setConfig(MouseUI::Status::FOCUSED, CANCEL_FOCUS_SOUND);

	MODEL(cancelButton, MouseUI*)->setClickAction(bind(&MainMenu::onCancel, this, _1));

	/* Configuro los textbox! */
	(*nameBox)[0]->getImages().setConfig(MouseUI::Status::IDLE, MAINMENU_TEXTBOX_IDLE);
	(*nameBox)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, MAINMENU_TEXTBOX_IDLE);
	(*nameBox)[0]->getImages().setConfig(MouseUI::Status::SELECTED, MAINMENU_TEXTBOX_SELECTED);
	(*nameBox)[0]->getImages().setConfig(MouseUI::Status::HOLDING, MAINMENU_TEXTBOX_SELECTED);
	(*nameBox)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, MAINMENU_TEXTBOX_SELECTED);

	(*ipBox)[0]->getImages().setConfig(MouseUI::Status::IDLE, MAINMENU_TEXTBOX_IDLE);
	(*ipBox)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, MAINMENU_TEXTBOX_IDLE);
	(*ipBox)[0]->getImages().setConfig(MouseUI::Status::SELECTED, MAINMENU_TEXTBOX_SELECTED);
	(*ipBox)[0]->getImages().setConfig(MouseUI::Status::HOLDING, MAINMENU_TEXTBOX_SELECTED);
	(*ipBox)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, MAINMENU_TEXTBOX_SELECTED);

	(*portBox)[0]->getImages().setConfig(MouseUI::Status::IDLE, MAINMENU_TEXTBOX_IDLE);
	(*portBox)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, MAINMENU_TEXTBOX_IDLE);
	(*portBox)[0]->getImages().setConfig(MouseUI::Status::SELECTED, MAINMENU_TEXTBOX_SELECTED);
	(*portBox)[0]->getImages().setConfig(MouseUI::Status::HOLDING, MAINMENU_TEXTBOX_SELECTED);
	(*portBox)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, MAINMENU_TEXTBOX_SELECTED);

	/* Agrego componentes */
	this->attachComponent(nameBox);
	this->attachComponent(ipBox);
	this->attachComponent(portBox);
	this->attachComponent(connectButton);
	this->attachComponent(cancelButton);
	this->attachComponent(status);
	this->attachComponent(message);

	/* Posicion de componentes */
	MODEL(nameBox, TextUI*)->setPosition(365, 230);
	MODEL(ipBox, TextUI*)->setPosition(365, 300);
	MODEL(portBox, TextUI*)->setPosition(365, 370);
	MODEL(connectButton, MouseUI*)->setPosition(400, 440);
	MODEL(cancelButton, MouseUI*)->setPosition(400, 440);
	MODEL(status, FrameUI*)->setPosition(0, 0);
	MODEL(message, TextUI*)->setPosition(10, 615);

	/* Configuro ventana general */
	this->setBackground(MAINMENU_BACKGROUND);
	this->setMusic(MAINMENU_MUSIC);
	this->setCloseAction(bind(&MainMenu::onExit, this, _1));

	/* Primer layout */
	_data_layout();
}

void
MainMenu::onExit(void* data) {

	/*
	* Cambio el estado del launcher a cerrado
	*/
	launcher.change(CatanLauncher::States::LAUNCHER_CLOSE);
}

void
MainMenu::onConnect(void* data) {

	/*
	* Busco la informacion correspondiente en los modelos
	* de la gui, utilizando los identificadores que se configuraron
	*/
	string name = MODEL((*this)["name"], TextUI*)->getText();
	string ip = MODEL((*this)["ip"], TextUI*)->getText();
	string sport = MODEL((*this)["port"], TextUI*)->getText();
	unsigned int port = 0;

	/* Verifico el estado de aquello que se recibe */
	if (sport.size()) {
		port = stoi(sport);
	}

	/*
	* Configuro los valores de los campos obtenidos, dentro de los correspondientes
	* lugares, como el nombre dentro del context en el launcher, y luego las ip y el port
	* en el networking.
	*/
	launcher.getContext().getGame().getLocalPlayer()->setName(name);
	launcher.getContext().getNetworking().setIp(ip);
	launcher.getContext().getNetworking().setPort(port);

	/* Inicializo el funcionamiento del networking */
	launcher.getContext().getNetworking().start();

	/* Cambio el layout */
	_connecting_layout();
}

void 
MainMenu::onCancel(void* data) {

	/*
	* Reinicio el estado del networking 
	*/
	launcher.getContext().getNetworking().reset();

	/*
	* Reinicio el estado de la imagen
	*/
	(*(*this)["status"])[0]->getImages().setConfig(IV_BITMAP, MAINMENU_STATUS_CLOSED);
	(*(*this)["status"])[0]->update();

	/*
	* Muestro el nuevo layout, volviendo a tomar datos
	*/
	_data_layout();
}

void
MainMenu::process(void) {
	/* Ejecuto procesos alternos al chequeo de los eventos
	* que se ejecuta para el funcionamiento de la interfaz grafica
	*/
	CatanNetworking::States state = launcher.getContext().getNetworking().getNetworkingState();

	/* Si hubo un cambio de estado en el networking
	* con respecto al anterior, reviso...
	*/
	if (prevState != state) {
		prevState = state;
		switch (state) {
			case CatanNetworking::States::CLOSED:
				(*(*this)["status"])[0]->getImages().setConfig(IV_BITMAP, MAINMENU_STATUS_CLOSED);
				(*(*this)["status"])[0]->update();
				break;
			case CatanNetworking::States::LISTENING:
			case CatanNetworking::States::DISCONNECTED:
				(*(*this)["status"])[0]->getImages().setConfig(IV_BITMAP, MAINMENU_STATUS_OFFLINE);
				(*(*this)["status"])[0]->update();
				break;
			case CatanNetworking::States::SYNC:
			case CatanNetworking::States::WAIT_SYNC:
				(*(*this)["status"])[0]->getImages().setConfig(IV_BITMAP, MAINMENU_STATUS_ONLINE);
				(*(*this)["status"])[0]->update();
				break;
			case CatanNetworking::States::NET_ERROR:
				(*(*this)["status"])[0]->getImages().setConfig(IV_BITMAP, MAINMENU_STATUS_ERROR);
				(*(*this)["status"])[0]->update();
				break;
			case CatanNetworking::States::IDLE:
				launcher.change(CatanLauncher::States::GAME_WINDOW);
				this->shutdown();
				break;
		}
	}

	/* Me fijo si el modo o estado actual del networking esta
	* en funcionamiento, para correr sus procesos... y luego verificar su estado!
	*/
	if (state != CatanNetworking::States::CLOSED && 
			state != CatanNetworking::States::IDLE &&
				state != CatanNetworking::States::NET_ERROR ) {
		CatanNetworking& net = launcher.getContext().getNetworking();

		/* Verifico en que estado se encuentra el networking, y en caso de
		* fallar, deberia indicar el error, volver al estado closed!
		*/
		if (net.good()) {
			net.run();
		}
	}

	/* Busco el label que contiene el mensaje informativo al usuario, con el cual
	* determino, por comparacion, si el mensaje interno se modifico, en cuyo caso,
	* lo informo mismo en el label
	*/
	string message = MODEL((*this)["message"], TextUI*)->getText();
	string newMessage = launcher.getContext().getNetworking().info();
	if (message != newMessage) {
		MODEL((*this)["message"], TextUI*)->setText(newMessage);
	}
}

void
MainMenu::_data_layout(void) {
	
	/* Activo los labels */
	MODEL((*this)["message"], TextUI*)->setEnable(true);
	MODEL((*this)["message"], TextUI*)->setVisible(true);

	/* Activo todas las imagenes */
	MODEL((*this)["status"], FrameUI*)->setEnable(true);
	MODEL((*this)["status"], FrameUI*)->setVisible(true);

	/* Activo todos los textboxs */
	MODEL((*this)["name"], TextUI*)->setEnable(true);
	MODEL((*this)["name"], TextUI*)->setVisible(true);
	MODEL((*this)["ip"], TextUI*)->setEnable(true);
	MODEL((*this)["ip"], TextUI*)->setVisible(true);
	MODEL((*this)["port"], TextUI*)->setEnable(true);
	MODEL((*this)["port"], TextUI*)->setVisible(true);

	/* Activo y pongo visible los buttons */
	MODEL((*this)["connect"], MouseUI*)->setEnable(true);
	MODEL((*this)["connect"], MouseUI*)->setVisible(true);
	MODEL((*this)["cancel"], MouseUI*)->setEnable(false);
	MODEL((*this)["cancel"], MouseUI*)->setVisible(false);

	draw();
}

void
MainMenu::_connecting_layout(void) {

	/* Activo los labels */
	MODEL((*this)["message"], TextUI*)->setEnable(true);
	MODEL((*this)["message"], TextUI*)->setVisible(true);

	/* Activo todas las imagnes */
	MODEL((*this)["status"], FrameUI*)->setEnable(true);
	MODEL((*this)["status"], FrameUI*)->setVisible(true);

	/* Activo todos los textboxs */
	MODEL((*this)["name"], TextUI*)->setEnable(false);
	MODEL((*this)["name"], TextUI*)->setVisible(true);
	MODEL((*this)["ip"], TextUI*)->setEnable(false);
	MODEL((*this)["ip"], TextUI*)->setVisible(true);
	MODEL((*this)["port"], TextUI*)->setEnable(false);
	MODEL((*this)["port"], TextUI*)->setVisible(true);

	/* Activo y pongo visible el button */
	MODEL((*this)["connect"], MouseUI*)->setEnable(false);
	MODEL((*this)["connect"], MouseUI*)->setVisible(false);
	MODEL((*this)["cancel"], MouseUI*)->setEnable(true);
	MODEL((*this)["cancel"], MouseUI*)->setVisible(true);

	draw();
}