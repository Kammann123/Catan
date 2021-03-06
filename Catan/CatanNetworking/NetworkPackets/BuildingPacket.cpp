#include "BuildingPacket.h"

PacketHeader buildingHeader(BuildingType type) {

	switch (type) {
		case BuildingType::SETTLEMENT:
			return PacketHeader::SETTLEMENT;
			break;
		case BuildingType::ROAD:
			return PacketHeader::ROAD;
			break;
		case BuildingType::CITY:
			return PacketHeader::CITY;
			break;
	}

	throw exception("BuildingPacket - Se ingreso un valor incorrecto para definir construccion");
}

BuildingType buildingType(PacketHeader header) {

	switch (header) {
		case PacketHeader::SETTLEMENT:
			return BuildingType::SETTLEMENT;
			break;
		case PacketHeader::CITY:
			return BuildingType::CITY;
			break;
		case PacketHeader::ROAD:
			return BuildingType::ROAD;
			break;
	}

	throw exception("BuildingPacket - Se ingreso un valor incorrecto para definir construccion");
}

BuildingPacket::
BuildingPacket(BuildingData data) : NetworkPacket(buildingHeader(data.getType())), BuildingData(data) {}

BuildingPacket::
BuildingPacket(PacketHeader header, Coord coords) : NetworkPacket(header), BuildingData() {
	this->setCoords(coords);
}

BuildingPacket::
BuildingPacket(PacketHeader header) : NetworkPacket(header), BuildingData() {

	switch (header) {
	case PacketHeader::SETTLEMENT:
		this->setType(BuildingType::SETTLEMENT);
		break;
	case PacketHeader::CITY:
		this->setType(BuildingType::CITY);
		break;
	case PacketHeader::ROAD:
		this->setType(BuildingType::ROAD);
		break;
	}
}

BuildingPacket::
~BuildingPacket() {}

unsigned char*
BuildingPacket::getDataStream(unsigned int& length) {

	Coord coords = this->getCoords();

	/* Calculo la cantidad */
	unsigned int bufferLength = 2 + (unsigned int)coords.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Guardo y armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = (unsigned char)coords.size();
	unsigned int i = 2;
	for (unsigned char c : coords) {
		buff[i++] = c;
	}

	/* Devuelvo */
	return buff;
}