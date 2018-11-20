#include "CatanNetworking/NetworkParsers/NameParser.h"
#include "CatanNetworking/NetworkParsers/MapParser.h"
#include "CatanNetworking/NetworkParsers/TokenParser.h"
#include "CatanNetworking/NetworkParsers/DevCardParser.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

	DevCardParser parser;
	unsigned char stream[] = { (unsigned char)PacketHeader::DEV_CARDS, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT, (unsigned char)DevCardId::KNIGHT };

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
				DevCardPacket* mapPacket = (DevCardPacket*)((DoneEvent*)response)->getPacket();
				for (unsigned int i = 0; i < 25; i++) {
					DevCardId card;
					mapPacket->getCard(card, i);
					cout << "Carta " << i << " - Valor: " << (unsigned char)card << endl;
				}
				getchar();
				return -1;
			}
		}
	}
}