#include "CatanNetworking/NetworkParsers/NameParser.h"
#include "CatanNetworking/NetworkParsers/MapParser.h"
#include "CatanNetworking/NetworkParsers/TokenParser.h"
#include "CatanNetworking/NetworkParsers/DevCardParser.h"
#include "CatanNetworking/NetworkParsers/DicesParser.h"
#include "CatanNetworking/NetworkParsers/RobberCardParser.h"
#include "CatanNetworking/NetworkParsers/RobberMoveParser.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

	RobberMoveParser parser;
	unsigned char stream[] = { (unsigned char)PacketHeader::ROBBER_MOVE, 'A'};

	for (unsigned char byte : stream) {

		GenericEvent* event = parser.generateEvent(byte);

		parser.cycle(event);

		GenericEvent* response = parser.getEvent();

		if (response) {

			if (response->getType() == ParserStatus::ERROR) {
				cout << ((ErrorEvent*)response)->getError().c_str() << endl;
				getchar();
				return -1;
			}
			else {
				cout << "Se parseo correctamente!" << endl;
				RobberMovePacket* robberMove = (RobberMovePacket*)((DoneEvent*)response)->getPacket();
				cout << "Posicion del robber: " << robberMove->getCoord() << endl;
				getchar();
				return -1;
			}
		}
	}
}