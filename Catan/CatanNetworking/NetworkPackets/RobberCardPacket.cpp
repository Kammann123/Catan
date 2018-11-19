#include "RobberCardPacket.h"

RobberCardPacket::
RobberCardPacket(void) : NetworkPacket(PacketHeader::ROBBER_CARDS) {
	this->resources.clear();
}

RobberCardPacket::
~RobberCardPacket() {}

void
RobberCardPacket::addResource(ResourceId resource) {
	this->resources.push_back(resource);
}

list<ResourceId>&
RobberCardPacket::getResources(void) {
	return this->resources;
}