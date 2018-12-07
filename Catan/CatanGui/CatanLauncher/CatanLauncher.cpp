#include "CatanLauncher.h"

CatanLauncher::
CatanLauncher() : game(), networking(game), mainmenu(*this), gamewindow(*this) {
	this->username = "";
	this->ip = "";
	this->port = 0;

	/* Configuraciones de los elementos */
	game.attach(&networking);
	game.attach(&gamewindow);

	/* Cambio de estado inicial */
	game.getCatanMap()->generateLand();
	game.getCatanMap()->generateSea();
	game.getCatanMap()->generateTokens();
	change(States::GAME_WINDOW);
}

void 
CatanLauncher::setUsername(string name)
{
	this->username = name;
}

void 
CatanLauncher::setIp(string ip)
{
	this->ip = ip;
}

void 
CatanLauncher::setPort(unsigned int port) {
	this->port = port;
}

string
CatanLauncher::getUsername(void)
{
	return username;
}

string 
CatanLauncher::getIp(void)
{
	return ip;
}

unsigned int 
CatanLauncher::getPort(void)
{
	return port;
}

CatanGame&
CatanLauncher::getGame(void)
{
	return game;
}

CatanNetworking& 
CatanLauncher::getNetworking(void)
{
	return networking;
}

void
CatanLauncher::run() {

	/* Se corren los estados del launcher, para determinar que
	* interfaz grafica se ejecuta, en caso de no estar abierta, se la abre.
	*/
	switch ( state ) {
		case MAIN_MENU:
			mainmenu.run();
			break;

		case GAME_WINDOW:
			gamewindow.run();
			break;
	}

	/* Me fijo si el modo o estado actual del networking esta
	* en funcionamiento, para correr sus procesos... y luego verificar su estado!
	*/
	CatanNetworking::States state = networking.getNetworkingState();
	if (state != CatanNetworking::States::CLOSED &&
		state != CatanNetworking::States::NET_ERROR) {

		/* Verifico en que estado se encuentra el networking, y en caso de
		* fallar, deberia indicar el error, volver al estado closed!
		*/
		if (networking.good()) {
			networking.run();
		}
	}
}

bool
CatanLauncher::alive(void) {
	return state != LAUNCHER_CLOSE;
}

void
CatanLauncher::change(States newState) {
	this->state = newState;

	/* Al cambiar de estado dentro del Launcher
	* se reconoce en cual estado me encontraba,
	* cierro las ventanas graficas de dicho estado
	* y posteriormente corro las siguientes 
	*/
	switch (state) {
	case MAIN_MENU:
		gamewindow.shutdown();
		mainmenu.start();
		break;

	case GAME_WINDOW:
		mainmenu.shutdown();
		gamewindow.start();
		break;
	}
}