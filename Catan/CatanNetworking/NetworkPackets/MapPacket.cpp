#include "MapPacket.h"

MapPacket::
MapPacket(void) : NetworkPacket(PacketHeader::MAP_IS) {
	this->gameMap.clear();
}

MapPacket::
~MapPacket(void) {}

bool 
MapPacket::setMapValue(unsigned char coord, MapValue value) {

	/* Valido posicion o coordenada */
	if ((coord >= '0' && coord <= '6') || (coord >= 'A' && coord <= 'S')) {
		gameMap[coord] = value;
		return true;
	}
	else {
		return false;
	}
}

map<unsigned char, MapValue>&
MapPacket::getMap(void) {

	return this->gameMap;
}