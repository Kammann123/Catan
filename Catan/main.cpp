#include "CatanNetworking/NetworkParsers/NameParser.h"
#include "CatanNetworking/NetworkParsers/MapParser.h"
#include "CatanNetworking/NetworkParsers/TokenParser.h"
#include "CatanNetworking/NetworkParsers/DevCardParser.h"
#include "CatanNetworking/NetworkParsers/DicesParser.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

	DicesParser parser;
	unsigned char stream[] = { (unsigned char)PacketHeader::MAP_IS, '2', '4'};

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
				DicesPacket* dicesPacket = (DicesPacket*)((DoneEvent*)response)->getPacket();
				cout << "Primer dado: " << to_string(dicesPacket->getFirstDice()) << endl;
				cout << "Segundo dado: " << to_string(dicesPacket->getSecondDice()) << endl;
				getchar();
				return -1;
			}
		}
	}
}