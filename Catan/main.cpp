#include "CatanNetworking/NetworkParsers/NameParser.h"
#include "CatanNetworking/NetworkParsers/MapParser.h"
#include "CatanNetworking/NetworkParsers/TokenParser.h"
#include "CatanNetworking/NetworkParsers/DevCardParser.h"
#include "CatanNetworking/NetworkParsers/DicesParser.h"
#include "CatanNetworking/NetworkParsers/RobberCardParser.h"
#include "CatanNetworking/NetworkParsers/RobberMoveParser.h"
#include "CatanNetworking/NetworkParsers/BuildingParser.h"
#include "CatanNetworking/NetworkParsers/BankParser.h"
#include "CatanNetworking/NetworkParsers/OfferParser.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

	OfferParser parser;
	unsigned char stream[] = { (unsigned char)PacketHeader::OFFER_TRADE, 2, 3, (unsigned char)ResourceId::DESERT , (unsigned char)ResourceId::DESERT, (unsigned char)ResourceId::FOREST, (unsigned char)ResourceId::FOREST, (unsigned char)ResourceId::FOREST };

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
				OfferPacket* offer = (OfferPacket*)((DoneEvent*)response)->getPacket();
				for (ResourceId r : offer->getGivenResources()) {

					cout << "Cede carta: " << (unsigned char)r << endl;
				}
				for (ResourceId r : offer->getReceivedResources()) {
					
					cout << "Recibe carta: " << (unsigned char)r << endl;
				}
				getchar();
			}
		}
	}
}