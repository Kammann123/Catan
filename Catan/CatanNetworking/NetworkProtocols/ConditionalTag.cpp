#include "ConditionalTag.h"

ConditionalTag::ConditionalTag(ConditionalCallback callback, string trueOption, string falseOption) : ProtocolTag() {
	this->callback = callback;
	this->trueOption = trueOption;
	this->falseOption = falseOption;
}

virtual string 
ConditionalTag::getTag(void) {
	if (this->callback()) {
		return this->trueOption;
	}
	else {
		return this->falseOption;
	}
}