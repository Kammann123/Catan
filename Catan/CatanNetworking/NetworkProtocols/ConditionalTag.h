#pragma once

#include "ProtocolTag.h"

/*
* ConditionalTag
* Permite definir que tag se escoge en base a un callback
*/
class ConditionalTag : public ProtocolTag {
public:
	ConditionalTag(ConditionalCallback callback, const char* trueOption, const char* falseOption);
	ConditionalTag(ConditionalCallback callback, string trueOption, string falseOption);
	virtual string getTag(void);
private:
	ConditionalCallback callback;
	string trueOption;
	string falseOption;
};