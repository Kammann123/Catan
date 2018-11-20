#include "YOPPacket.h"

YOPPacket::
YOPPacket(void) : NetworkPacket(PacketHeader::YEARS_OF_PLENTY) {}

YOPPacket::
~YOPPacket() {}

bool
YOPPacket::setFirstResource(ResourceId resource) {

	return _set_resource(ResourceIndex::FIRST, resource);
}

bool
YOPPacket::setSecondResource(ResourceId resource) {

	return _set_resource(ResourceIndex::SECOND, resource);
}

ResourceId
YOPPacket::getFirstResource(void) {
	return this->resources[ResourceIndex::FIRST];
}

ResourceId
YOPPacket::getSecondResource(void) {
	return this->resources[ResourceIndex::SECOND];
}

bool 
YOPPacket::_set_resource(ResourceIndex index, ResourceId resource) {

	if (isResourceValue(resource)) {
		this->resources[index] = resource;
		return true;
	}
	else {
		return false;
	}
}

unsigned char*
YOPPacket::getDataStream(unsigned int& length) {

	unsigned int bufferLength = 3;

	unsigned char* buff = new unsigned char[bufferLength];

	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	buff[1] = (unsigned char)this->resources[ResourceIndex::FIRST];
	buff[2] = (unsigned char)this->resources[ResourceIndex::SECOND];

	return buff;
}