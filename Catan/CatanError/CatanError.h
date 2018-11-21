#pragma once
#include <string>
#include "../CatanGame/CatanGame.h"

using namespace std;

enum class ErrorID {NETWORK_ERROR, NON_VALID_ACTION, NETWORK_TIMEOUT, NO_ERROR};

class CatanError {
public:
	CatanError();
	~CatanError();
	ErrorID getID(void);
	void setID(ErrorID newID);
	string& getDescription(void);
	void setDescription(string& newDescription);

private:
	ErrorID ID;
	string description;
	Sources source;

};