#include "NetworkPacket.h"

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