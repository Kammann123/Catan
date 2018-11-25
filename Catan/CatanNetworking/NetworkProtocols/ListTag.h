#pragma once

#include "ProtocolTag.h"

#include <vector>

using namespace std;

/*
* ListTag
* Permite definir que tag se escoge en base a un callback
*/
class ListTag : public ProtocolTag {
public:
	ListTag(ListCallback callback, vector<string> values);
	virtual string getTag(void);
private:
	ListCallback callback;
	vector<string> values;
};