#include "CatanNetworking/NetworkParsers/NameParser.h"
#include "CatanNetworking/NetworkParsers/MapParser.h"
#include "CatanNetworking/NetworkParsers/TokenParser.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

	TokenParser parser;
	unsigned char stream[] = { (unsigned char)PacketHeader::CIRCULAR_TOKENS, 0, 2, 3, 6, 5, 7, 9, 8, 8, 8, 12, 11, 11, 10 , 10 , 10 , 10 , 10, 5 };

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
				TokenPacket* mapPacket = (TokenPacket*)((DoneEvent*)response)->getPacket();
				map<unsigned char, unsigned char> tokenMap = mapPacket->getTokens();
				for (auto mapValue : tokenMap) {
					cout << "Posicion: " << mapValue.first << " Token: " << to_string(mapValue.second) << endl;
				}
				getchar();
				return -1;
			}
		}
	}
}