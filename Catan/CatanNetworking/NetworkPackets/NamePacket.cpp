#include "NamePacket.h"

NamePacket::
NamePacket(void) : NetworkPacket(PacketHeader::NAME_IS) {

	name.clear();
}

NamePacket::
~NamePacket(void) {}

void
NamePacket::setName(string& name) {

	this->name = name;
}

void
NamePacket::setName(char letter) {

	this->name += letter;
}

string&
NamePacket::getName(void) {

	return this->name;
}