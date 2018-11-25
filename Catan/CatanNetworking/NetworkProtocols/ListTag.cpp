#include "ListTag.h"

ListTag::
ListTag(ListCallback callback, vector<string> values) : ProtocolTag() {
	this->callback = callback;
	this->values = values;
}

string
ListTag::getTag(void) {

	return this->values[this->callback()];
}