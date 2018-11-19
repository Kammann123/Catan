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

unsigned char*
MapPacket::getDataStream(unsigned int& length) {

	/* Calculo la longitud de buffer */
	unsigned int bufferLength = 1 + gameMap.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Guardo y armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	unsigned int ii = 1;
	for (unsigned char i = 0; i <= 6; i++) {
		if (gameMap.find(i) != gameMap.end()) {
			buff[ii++] = gameMap[i];
		}
	}
	for (unsigned char i = 'A'; i <= 'S'; i++) {
		if (gameMap.find(i) != gameMap.end()) {
			buff[ii++] = gameMap[i];
		}
	}

	/* Devuelvo */
	return buff;
}