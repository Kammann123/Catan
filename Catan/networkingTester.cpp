#include "CatanNetworking/CatanNetworking.h"
#include "CatanGame/CatanGame.h"

#include <Windows.h>
#include <conio.h>
#include <vector>

#include "CatanEvents/BuildingEvent.h"
#include "CatanEvents/DicesEvent.h"

using namespace std;

#define CONSOLE(msg)	cout << "[TESTING] " << msg << endl;

CatanEvent* ui(void);
CatanEvent* build(void);
CatanEvent* dices(void);
CatanEvent* random_dices(void);

int main(int argc, char** argv) {
	string localName;
	string ip;
	unsigned int port;
	CONSOLE("Ingrese su nombre: ")
	cin >> localName;
	CONSOLE("Ingrese ip: ");
	cin >> ip;
	CONSOLE("Ingrese port: ");
	cin >> port;

	CatanGame game = CatanGame(localName);
	CatanNetworking net = CatanNetworking(ip, port, game);
	game.attach(&net);
	
	CatanNetworking::States netStatus = CatanNetworking::States::DISCONNECTED;
	CatanGame::State gameStatus = CatanGame::State::GAME_SYNC;

	while (game.getState() != CatanGame::State::GAME_ERROR && game.getState() != CatanGame::State::GAME_END) {

		/* Corremos la ui */
		if (_kbhit()) {
			CatanEvent* event = ui();
			if (event) {
				game.handle(event);
			}
		}

		/* Corremos el networking */
		if (net.good()) {
			net.run();

			if (netStatus != net.getNetworkingState()) {
				netStatus = net.getNetworkingState();
				CONSOLE("Networking cambio de estado: " + string((char*)net.getNetworkingString()));
			}
		}
		else {
			CONSOLE("Hubo un error durante la ejecucion de networking!");
			CONSOLE(net.getError());
			break;
		}

		/* Corremos el juego */
		if (gameStatus != game.getState()) {
			gameStatus = game.getState();
			if(gameStatus == CatanGame::State::FIRST_BUILDS){
				CONSOLE("Juega el jugador " + string((char*)(game.getTurn() == PlayerId::PLAYER_ONE? "LOCAL" : "OPONENTE")));
			}
			CONSOLE("Game cambio de estado: " + string((char*)game.getStateString()));
			CONSOLE(game.info());
		}
	}

	if (game.getState() == CatanGame::State::GAME_ERROR) {
		CONSOLE("El juego tuvo un error durante su ejecucion.");
	}
	else if (game.getState() == CatanGame::State::GAME_END) {
		CONSOLE("El juego ha finalizado.");
	}
	CONSOLE(game.info());
	getchar();

	return 0;
}

CatanEvent* ui(void) {
	unsigned char buff = _getch();

	cout << "[UserInterface] Hola Mortal, al momento de ahora puedes hacer las siguientes funciones:" << endl
		<< "\t+ \"B\": Realizar una construccion" << endl
		<< "\t+ \"D\": Tirar dados elegidos" << endl
		<< "\t+ \"R\": Tirar dados al azar" << endl;

	cout << "Eleccion: ";
	cin >> buff;
	_getch();

	switch( buff ){
		
		case 'B':
			return build();
			break;

		case 'R':
			return random_dices();
			break;

		case 'D':
			return dices();
			break;

		default:
			return nullptr;
			break;

	}

}

CatanEvent* build(void) {

	cout << endl << "[Construccion]" << endl;

	unsigned char type;
	string coords;

	cout << "Tipo de construccion? (S: settlement - R: road - C: city) > ";
	cin >> type;
	cout << endl << "Coordenadas? > ";
	cin >> coords;

	switch (type) {
		case 'S':
			return new BuildingEvent(coords, BuildingType::SETTLEMENT);
			break;
		case 'R':
			return new BuildingEvent(coords, BuildingType::ROAD);
			break;
		case 'C':
			return new BuildingEvent(coords, BuildingType::CITY);
			break;
		default:
			return nullptr;
			break;
	}
}

CatanEvent* dices(void) {

	unsigned int fDice, sDice;

	cout << "Primer dado: ";
	cin >> fDice;
	cout << endl << "Segundo dado: ";
	cin >> sDice;

	CatanEvent* dicesEvent = new DicesEvent(fDice, sDice, PlayerId::PLAYER_ONE);

	return dicesEvent;

}

CatanEvent* random_dices(void) {
	unsigned char fDice = RANDOM_DICE;
	unsigned char sDice = RANDOM_DICE;

	CatanEvent* dicesEvent = new DicesEvent(fDice, sDice, PlayerId::PLAYER_ONE);

	return dicesEvent;
}