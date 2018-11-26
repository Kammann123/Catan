#include "CatanNetworking/CatanNetworking.h"
#include "CatanGame/CatanGame.h"

#define CONSOLE(x) cout << "[CatanGame v1.0] " << x << endl

int main(int argc, char** argv) {

	CatanGame game("Lucas");

	game.generateMap();
	game.generateOcean();
	game.generateTokens();
	game.generateTurn();

	for (auto hex : game.seaMap) {
		cout << "Coordenada: " << hex.first << " Cantidad de puertos: " << hex.second.getDocks().size();
		for (SeaId dock : hex.second.getDocks()) {
			cout << " Dock: " << (unsigned char)dock;
		}
		cout << endl;
	}
	for (auto hex : game.resourceMap) {
		cout << "Coordenada: " << hex.first << " Recurso: " << (unsigned char)hex.second.getResource() << " Token: " << hex.second.getToken() << endl;
	}
	cout << "Es turno del jugador: " << (unsigned int)game.turn << endl;
}