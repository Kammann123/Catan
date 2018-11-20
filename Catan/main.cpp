#include "CatanNetworking/NetworkParsers/NameParser.h"
#include "CatanNetworking/NetworkParsers/MapParser.h"
#include "CatanNetworking/NetworkParsers/TokenParser.h"
#include "CatanNetworking/NetworkParsers/DevCardParser.h"
#include "CatanNetworking/NetworkParsers/DicesParser.h"
#include "CatanNetworking/NetworkParsers/RobberCardParser.h"
#include "CatanNetworking/NetworkParsers/RobberMoveParser.h"
#include "CatanNetworking/NetworkParsers/BuildingParser.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

	BuildingParser parser;
	unsigned char stream[] = { (unsigned char)PacketHeader::SETTLEMENT, 3, 'A', 'B', 'C', (unsigned char)PacketHeader::ROAD, 2, 'A', 'B', (unsigned char)PacketHeader::CITY, 3, 'A', 'B', 'C', (unsigned char)PacketHeader::CITY, 2, 'Z'};

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
				BuildingPacket* building = (BuildingPacket*)((DoneEvent*)response)->getPacket();
				cout << "Construccion: " << (unsigned char)building->getHeader() << " Coordenadas: " << building->getCoords() << endl;
				getchar();
			}
		}
	}
}