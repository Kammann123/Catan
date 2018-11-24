#include "MapPacket.h"

MapPacket::
MapPacket(MapData data) : NetworkPacket(PacketHeader::MAP_IS), MapData(data) {}

MapPacket::
MapPacket(void) : NetworkPacket(PacketHeader::MAP_IS), MapData() {}

MapPacket::
MapPacket(map<unsigned char, MapValue> m) : NetworkPacket(PacketHeader::MAP_IS), MapData(m) {}

MapPacket::
~MapPacket(void) {}

unsigned char*
MapPacket::getDataStream(unsigned int& length) {

	map<unsigned char, MapValue> gameMap = this->getMap();

	/* Calculo la longitud de buffer */
	unsigned int bufferLength = 1 + (unsigned int)gameMap.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Guardo y armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	unsigned int ii = 1;
	for (unsigned char i = '0'; i <= '5'; i++) {
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