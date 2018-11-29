#include "CatanNetworking/CatanNetworking.h"
#include "CatanGame/CatanGame.h"

#include <Windows.h>
#include <conio.h>
#include <vector>

#include "CatanEvents/BuildingEvent.h"
#include "CatanEvents/DicesEvent.h"
#include "CatanEvents/RobberCardEvent.h"
#include "CatanEvents/RobberMoveEvent.h"
#include "CatanEvents/BankEvent.h"
#include "CatanEvents/OfferEvent.h"

using namespace std;

#define CONSOLE(msg)	cout << "[TESTING] " << msg << endl;

CatanEvent* ui(CatanGame& game);
CatanEvent* build(void);
CatanEvent* dices(void);
CatanEvent* random_dices(void);
CatanEvent* bank_trade(void);
CatanEvent* pass(void);
CatanEvent* dock_trade(void);
CatanEvent* robber_move(void);
CatanEvent* robber_cards(void);
CatanEvent* offer_trade(void);

void gui(CatanGame& game);

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
			CatanEvent* event = ui(game);
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

void gui(CatanGame& game) {

	Player player = game.getPlayer(PlayerId::PLAYER_ONE);
	list<ResourceCard*> cards = player.showCards();

	cout << "[UserStatus] Hola, " << player.getName() << " tenes " << player.getVictoryPoints() << " puntos" << endl;
	cout << string((char*)(game.isLongestRoad(PlayerId::PLAYER_ONE) ? "Ademas, sos el longest road, campeon!" : "Lamentablemente, no tenes caminos muy largos...")) << endl;
	cout << endl << "\t -Tus cartas-" << endl;
	cout << "Lumber Cards: " << player.getResourceCount(ResourceId::FOREST) << endl;
	cout << "Brick Cards: " << player.getResourceCount(ResourceId::HILL) << endl;
	cout << "Wool Cards: " << player.getResourceCount(ResourceId::PASTURES) << endl;
	cout << "Ore Cards: " << player.getResourceCount(ResourceId::MOUNTAIN) << endl;
	cout << "Grain Cards: " << player.getResourceCount(ResourceId::FIELD) << endl;
	cout << endl << "\t -Tus fichas-" << endl;
	cout << "Settlements disponibles: " << player.hasSettlements() << endl;
	cout << "Roads disponibles: " << player.hasRoads() << endl;
	cout << "Cities disponibles: " << player.hasCities() << endl;
}

CatanEvent* ui(CatanGame& game) {
	unsigned char buff = _getch();

	cout << "[UserInterface] Hola Mortal, al momento de ahora puedes hacer las siguientes funciones:" << endl
		<< "\t+ \"B\": Realizar una construccion" << endl
		<< "\t+ \"D\": Tirar dados elegidos" << endl
		<< "\t+ \"R\": Tirar dados al azar" << endl
		<< "\t+ \"T\": Intercambiar con el banco" << endl
		<< "\t+ \"M\": Intercambiar con el muelle" << endl
		<< "\t+ \"O\": Intercambiar con el usuario" << endl
		<< "\t+ \"P\": Pasar de turno" << endl
		<< "\t+ \"L\": Mover el robber" << endl
		<< "\t+ \"U\": Descartar cartas Robber Cards!" << endl
		<< "\t+ \"I\": Informacion del player" << endl;

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

		case 'T':
			return bank_trade();
			break;

		case 'P':
			return pass();
			break;

		case 'M':
			return dock_trade();
			break;
		
		case 'I':
			gui(game);
			return nullptr;
			break;

		case 'L':
			return robber_move();
			break;

		case 'U':
			return robber_cards();
			break;

		case 'O':
			return offer_trade();
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

	CatanEvent* dicesEvent = new DicesEvent(fDice-'0', sDice - '0', PlayerId::PLAYER_ONE);

	return dicesEvent;

}

CatanEvent* random_dices(void) {
	unsigned char fDice = RANDOM_DICE;
	unsigned char sDice = RANDOM_DICE;

	CatanEvent* dicesEvent = new DicesEvent(fDice, sDice, PlayerId::PLAYER_ONE);

	return dicesEvent;
}

CatanEvent* bank_trade(void) {
	cout << "[Intercambio con banco]" << endl;
	cout << "Cartas para dar: " << endl;
	cout << "\t" << "+0: Lumber" << endl;
	cout << "\t" << "+1: Brick" << endl;
	cout << "\t" << "+2: Ore" << endl;
	cout << "\t" << "+3: Grain" << endl;
	cout << "\t" << "+4: Wool" << endl;
	unsigned char give;
	cin >> give;
	if (give >= '0' && give <= '4') {

		ResourceId giveId = ResourceId::DESERT;

		switch (give) {
		case '0':
			giveId = ResourceId::FOREST;
			break;
		case '1':
			giveId = ResourceId::HILL;
			break;
		case '2':
			giveId = ResourceId::MOUNTAIN;
			break;
		case '3':
			giveId = ResourceId::FIELD;
			break;
		case '4':
			giveId = ResourceId::PASTURES;
			break;
		}

		list<ResourceId> givenResources;
		for (unsigned int i = 4; i > 0; i--) {
			givenResources.push_back(giveId);
		}

		cout << "Vas a dar 4 de esas cartas, y que queres recibir? " << endl;
		cout << "\t" << "+0: Lumber" << endl;
		cout << "\t" << "+1: Brick" << endl;
		cout << "\t" << "+2: Ore" << endl;
		cout << "\t" << "+3: Grain" << endl;
		cout << "\t" << "+4: Wool" << endl;
		unsigned char recv;
		cin >> recv;

		if (recv >= '0' && recv <= '4') {


			ResourceId recvId = ResourceId::DESERT;

			switch (recv) {
			case '0':
				recvId = ResourceId::FOREST;
				break;
			case '1':
				recvId = ResourceId::HILL;
				break;
			case '2':
				recvId = ResourceId::MOUNTAIN;
				break;
			case '3':
				recvId = ResourceId::FIELD;
				break;
			case '4':
				recvId = ResourceId::PASTURES;
				break;
			}
			list<ResourceId> recvResources;
			recvResources.push_back(recvId);

			return new BankEvent(givenResources, recvResources);
		}
	}

	return nullptr;
}

CatanEvent* dock_trade(void) {
	cout << "[Intercambio con muelle]" << endl;
	cout << "Cartas para dar: " << endl;
	cout << "\t" << "+0: Lumber" << endl;
	cout << "\t" << "+1: Brick" << endl;
	cout << "\t" << "+2: Ore" << endl;
	cout << "\t" << "+3: Grain" << endl;
	cout << "\t" << "+4: Wool" << endl;
	unsigned char give;
	cin >> give;
	if (give >= '0' && give <= '4') {

		ResourceId giveId = ResourceId::DESERT;

		switch (give) {
		case '0':
			giveId = ResourceId::FOREST;
			break;
		case '1':
			giveId = ResourceId::HILL;
			break;
		case '2':
			giveId = ResourceId::MOUNTAIN;
			break;
		case '3':
			giveId = ResourceId::FIELD;
			break;
		case '4':
			giveId = ResourceId::PASTURES;
			break;
		}

		cout << "Cantidad entregadas: " << endl;
		unsigned char amount = 0;
		cin >> amount;

		list<ResourceId> givenResources;
		for (unsigned int i = amount; i > 0; i--) {
			givenResources.push_back(giveId);
		}

		cout << "Vas a dar 4 de esas cartas, y que queres recibir? " << endl;
		cout << "\t" << "+0: Lumber" << endl;
		cout << "\t" << "+1: Brick" << endl;
		cout << "\t" << "+2: Ore" << endl;
		cout << "\t" << "+3: Grain" << endl;
		cout << "\t" << "+4: Wool" << endl;
		unsigned char recv;
		cin >> recv;

		if (recv >= '0' && recv <= '4') {


			ResourceId recvId = ResourceId::DESERT;

			switch (recv) {
			case '0':
				recvId = ResourceId::FOREST;
				break;
			case '1':
				recvId = ResourceId::HILL;
				break;
			case '2':
				recvId = ResourceId::MOUNTAIN;
				break;
			case '3':
				recvId = ResourceId::FIELD;
				break;
			case '4':
				recvId = ResourceId::PASTURES;
				break;
			}
			list<ResourceId> recvResources;
			recvResources.push_back(recvId);

			return new BankEvent(givenResources, recvResources);
		}
	}

	return nullptr;
}

CatanEvent* pass(void) {

	return new CatanEvent(CatanEvent::Events::PASS, CatanEvent::Sources::GUI, PlayerId::PLAYER_ONE);
}

CatanEvent* robber_move(void) {

	cout << "[Mover el robber]" << endl;
	unsigned char coord;
	cout << "Nueva coordenada: " << endl;
	cin >> coord;

	return new RobberMoveEvent(coord, PlayerId::PLAYER_ONE);
}

CatanEvent* robber_cards(void) {

	cout << "[Robber Cards - Descartar cartas]" << endl;
	cout << "Descartar Lumber (cantidad): ";
	unsigned int lumber;
	cin >> lumber;
	cout << "Descartar Brick (cantidad): ";
	unsigned int brick;
	cin >> brick;
	cout << "Descartar Ore (cantidad): ";
	unsigned int ore;
	cin >> ore;
	cout << "Descartar Grain (cantidad): ";
	unsigned int grain;
	cin >> grain;
	cout << "Descartar Wool (cantidad): ";
	unsigned int wool;
	cin >> wool;

	list<ResourceId> cards;
	for (unsigned int i = lumber; i > 0; i--) {
		cards.push_back(ResourceId::FOREST);
	}
	for (unsigned int i = brick; i > 0; i--) {
		cards.push_back(ResourceId::HILL);
	}
	for (unsigned int i = ore; i > 0; i--) {
		cards.push_back(ResourceId::MOUNTAIN);
	}
	for (unsigned int i = grain; i > 0; i--) {
		cards.push_back(ResourceId::FIELD);
	}
	for (unsigned int i = wool; i > 0; i--) {
		cards.push_back(ResourceId::PASTURES);
	}

	return new RobberCardEvent(cards, PlayerId::PLAYER_ONE);
}

CatanEvent* offer_trade(void) {
	cout << "[Intercambio entre usuarios]" << endl;
	cout << "\t\t-Cartas ofrecidas:" << endl;
	cout << "Dar Lumber (cantidad): ";
	unsigned int lumber;
	cin >> lumber;
	cout << "Dar Brick (cantidad): ";
	unsigned int brick;
	cin >> brick;
	cout << "Dar Ore (cantidad): ";
	unsigned int ore;
	cin >> ore;
	cout << "Dar Grain (cantidad): ";
	unsigned int grain;
	cin >> grain;
	cout << "Dar Wool (cantidad): ";
	unsigned int wool;
	cin >> wool;

	list<ResourceId> given;
	for (unsigned int i = lumber; i > 0; i--) {
		given.push_back(ResourceId::FOREST);
	}
	for (unsigned int i = brick; i > 0; i--) {
		given.push_back(ResourceId::HILL);
	}
	for (unsigned int i = ore; i > 0; i--) {
		given.push_back(ResourceId::MOUNTAIN);
	}
	for (unsigned int i = grain; i > 0; i--) {
		given.push_back(ResourceId::FIELD);
	}
	for (unsigned int i = wool; i > 0; i--) {
		given.push_back(ResourceId::PASTURES);
	}
	cout << "\t\t-Cartas pedidas:" << endl;
	cout << "Pedir Lumber (cantidad): ";
	cin >> lumber;
	cout << "Pedir Brick (cantidad): ";
	cin >> brick;
	cout << "Pedir Ore (cantidad): ";
	cin >> ore;
	cout << "Pedir Grain (cantidad): ";
	cin >> grain;
	cout << "Pedir Wool (cantidad): ";
	cin >> wool;

	list<ResourceId> recv;
	for (unsigned int i = lumber; i > 0; i--) {
		recv.push_back(ResourceId::FOREST);
	}
	for (unsigned int i = brick; i > 0; i--) {
		recv.push_back(ResourceId::HILL);
	}
	for (unsigned int i = ore; i > 0; i--) {
		recv.push_back(ResourceId::MOUNTAIN);
	}
	for (unsigned int i = grain; i > 0; i--) {
		recv.push_back(ResourceId::FIELD);
	}
	for (unsigned int i = wool; i > 0; i--) {
		recv.push_back(ResourceId::PASTURES);
	}

	return new OfferEvent(given, recv, PlayerId::PLAYER_ONE);
}