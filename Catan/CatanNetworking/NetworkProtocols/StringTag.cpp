#include "StringTag.h"

StringTag::StringTag(string tag) : ProtocolTag() {
	this->tag = tag;
}

string
StringTag::getTag(void) {
	return this->tag;
}