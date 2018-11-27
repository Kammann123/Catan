#include "CatanNetworking/CatanNetworking.h"
#include "CatanGame/CatanGame.h"

using namespace std;

#define CONSOLE(msg)	cout << "[TESTING] " << msg << endl;

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

	string netStatus = "";
	CatanGame::State gameStatus = CatanGame::State::GAME_SYNC;

	while (game.getState() != CatanGame::State::GAME_ERROR && game.getState() != CatanGame::State::GAME_END) {

		if (net.good()) {
			net.run();

			if (netStatus != net.what()) {
				netStatus = net.what();
				CONSOLE("Networking cambio de estado: " + netStatus);
			}

		}
		else {
			CONSOLE("Hubo un error durante la ejecucion de networking!");
			CONSOLE(net.getError());
			break;
		}

		if (gameStatus != game.getState()) {
			gameStatus = game.getState();
			CONSOLE("Game cambio de estado: " + gameStatus);
		}
	}

	if (game.getState() == CatanGame::State::GAME_ERROR) {
		CONSOLE("El juego tuvo un error durante su ejecucion.");
	}
	else if(game.getState() == CatanGame::State::GAME_END) {
		CONSOLE("El juego ha finalizado.");
	}
	CONSOLE(game.info());
	getchar();

	return 0;
}