#include "NetworkPacket.h"

map<PacketHeader, const char*> HeaderStrings = {
{ OTHER, "OTHER" },{ ACK, "ACK" },{ NAME, "NAME" },{ NAME_IS, "NAME_IS" },{ MAP_IS, "MAP_IS" },{ CIRCULAR_TOKENS, "CIRCULAR_TOKENS" },
{ PLAY_WITH_DEV, "PLAY_WITH_DEV" },{ DEV_CARDS, "DEV_CARDS" },{ YOU_START, "YOU_START" },{ I_START, "I_START" },
{ DICES_ARE, "DICES_ARE" },{ ROBBER_CARDS, "ROBBER_CARDS" },{ CARD_IS, "CARD_IS" },{ ROBBER_MOVE, "ROBBER_MOVE" },
{ SETTLEMENT, "SETTLEMENT" },{ ROAD, "ROAD" },{ CITY, "CITY" },{ BANK_TRADE, "BANK_TRADE" },{ OFFER_TRADE, "OFFER_TRADE" },
{ PASS, "PASS" },{ DEV_CARD, "DEV_CARD" },{ MONOPOLY, "MONOPOLY" },{ YEARS_OF_PLENTY, "YEARS_OF_PLENTY" },
{ ROAD_BUILDING, "ROAD_BUILDING" },{ KNIGHT, "KNIGHT" },{ YES, "YES" },{ NO, "NO" },{ I_WON, "I_WON" },{ PLAY_AGAIN, "PLAY_AGAIN" },
{ GAME_OVER, "GAME_OVER" },{ ERROR, "ERROR" },{ QUIT, "QUIT" }
};

/* NetworkPacket Metodos Definiciones */

NetworkPacket::
NetworkPacket(PacketHeader header) {

	this->header = header;
}

NetworkPacket::
~NetworkPacket() {}

PacketHeader
NetworkPacket::getHeader(void) const {

	return this->header;
}

string
NetworkPacket::getString(void) {
	string msg = "[NetworkPacket] " + string(HeaderStrings[getHeader()]);
	return msg;
}

unsigned char*
NetworkPacket::getDataStream(unsigned int& length) {

	/* Armo el mensaje o paquete */
	unsigned char* buff = new unsigned char[1];

	/* Guardo el dato */
	buff[0] = (unsigned char)this->header;
	length = 1;

	return buff;
}