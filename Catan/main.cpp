#include "CatanNetworking/NetworkParsers/NameParser.h"
#include "CatanNetworking/NetworkParsers/MapParser.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	MapParser parser;
	unsigned char stream[] = { (unsigned char)PacketHeader::MAP_IS, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD, (unsigned char)ResourceId::FIELD };

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
				MapPacket* mapPacket = (MapPacket*)((DoneEvent*)response)->getPacket();
				map<unsigned char, MapValue> gameMap = mapPacket->getMap();
				for (auto mapValue : gameMap) {
					cout << "Posicion: " << mapValue.first << " Recurso: " << mapValue.second << endl;
				}
				getchar();
				return -1;
			}
		}
	}
}