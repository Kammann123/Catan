#include "../Catan/CatanNetworking/CatanNetworking.h"
#include "../Catan/CatanGame/CatanGame.h"

#define CONSOLE(x) cout << "[CatanGame v1.0] " << x << endl

int main(int argc, char** argv) {

	CatanGame game("Juan Carlos Catan");
	CatanNetworking net("127.0.0.1", 12345, game);

	game.attach(&net);

	CONSOLE("Iniciando networking y game...");

	string status = net.what();
	CONSOLE("Estado inicial " + status);

	while (net.good()) {

		net.run();

		if (status != net.what()) {

			CONSOLE("Hubo un cambio de estado en el networking " + net.what());

			status = net.what();
		}

	}

	CONSOLE(net.getError());

}