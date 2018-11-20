#include "CatanNetworking/NetworkParsers/NameParser.h"
#include "CatanNetworking/NetworkParsers/MapParser.h"
#include "CatanNetworking/NetworkParsers/TokenParser.h"
#include "CatanNetworking/NetworkParsers/DevCardParser.h"
#include "CatanNetworking/NetworkParsers/DicesParser.h"
#include "CatanNetworking/NetworkParsers/RobberCardParser.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

	RobberCardParser parser;
	unsigned char stream[] = { (unsigned char)PacketHeader::ROBBER_CARDS, 3, (unsigned char)ResourceId::HILL , (unsigned char)ResourceId::FOREST , (unsigned char)ResourceId::FOREST };

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
				RobberCardPacket* robberCards = (RobberCardPacket*)((DoneEvent*)response)->getPacket();
				for (auto r : robberCards->getResources()) {
					cout << "Desechando carta: " << (unsigned char)r << endl;
				}
				getchar();
				return -1;
			}
		}
	}
}