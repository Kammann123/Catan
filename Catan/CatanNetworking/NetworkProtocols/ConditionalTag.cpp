#include "ConditionalTag.h"

ConditionalTag::ConditionalTag(ConditionalCallback callback, const char* trueOption, const char* falseOption) {
	this->callback = callback;
	this->trueOption = trueOption;
	this->falseOption = falseOption;
}

ConditionalTag::ConditionalTag(ConditionalCallback callback, string trueOption, string falseOption) : ProtocolTag() {
	this->callback = callback;
	this->trueOption = trueOption;
	this->falseOption = falseOption;
}

string 
ConditionalTag::getTag(void) {
	if (this->callback()) {
		return this->trueOption;
	}
	else {
		return this->falseOption;
	}
}