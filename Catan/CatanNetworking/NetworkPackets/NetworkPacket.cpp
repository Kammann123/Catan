#include "NetworkPacket.h"

#define IS(value, compareValue, cast) ((value) == (cast)(compareValue))

/* Funciones */
bool isMapValue(unsigned char value) {

	return isSeaValue(value) || isResourceValue(value);
}

bool isSeaValue(unsigned char value) {
	
	return (
		IS(value, SeaId::NORMAL, unsigned char) ||
		IS(value, SeaId::WHEAT, unsigned char) || 
		IS(value, SeaId::SHEEP, unsigned char) ||
		IS(value, SeaId::BRICK, unsigned char) ||
		IS(value, SeaId::STONE, unsigned char) ||
		IS(value, SeaId::WOOD, unsigned char)
	);
}

bool isResourceValue(unsigned char value) {
	
	return (
		IS(value, ResourceId::FOREST, unsigned char) ||
		IS(value, ResourceId::HILL, unsigned char) ||
		IS(value, ResourceId::MOUNTAIN, unsigned char) ||
		IS(value, ResourceId::FIELD, unsigned char) ||
		IS(value, ResourceId::PASTURES, unsigned char) ||
		IS(value, ResourceId::DESERT, unsigned char)
	);
}

bool isValidToken(unsigned char value) {

	if( value == 0 || (value >= 2 && value <= 6) || (value >= 8 && value <= 12) ){
		return true;
	}
	else {
		return false;
	}
}

bool isDevCard(unsigned char value) {

	return(
		IS(value, DevCardId::KNIGHT, unsigned char) ||
		IS(value, DevCardId::VICTORY_POINT, unsigned char) ||
		IS(value, DevCardId::ROAD_BUILD, unsigned char) ||
		IS(value, DevCardId::MONOPOLY, unsigned char) ||
		IS(value, DevCardId::PLENITY_YEAR, unsigned char)
	);
}

bool isValidDice(unsigned char value) {
	return (value >= '1' && value <= '6');
}

bool isMapPosition(unsigned char value) {
	return (value >= 'A' && value <= 'S');
}

bool isSeaPosition(unsigned char value) {
	return (value >= '0' && value <= '5');
}

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

unsigned char*
NetworkPacket::getDataStream(unsigned int& length) {

	/* Armo el mensaje o paquete */
	unsigned char* buff = new unsigned char[1];

	/* Guardo el dato */
	buff[0] = (unsigned char)this->header;
	length = 1;

	return buff;
}