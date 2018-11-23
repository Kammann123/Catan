#pragma once

#include "CatanData.h"

#include <list>

using namespace std;

/*
* BankData
* Implementacion de la informacion de una transaccion bancaria o maritima
*/
class BankData : public CatanData {
public:

	/* Constructor */
	BankData(list<ResourceId> given, list<ResourceId> recv);
	BankData();

	/*
	* Getters y setters
	*/
	void addGiven(ResourceId res);
	void addReceived(ResourceId res);
	list<ResourceId>& getGiven(void);
	list<ResourceId>& getRecv(void);

private:
	list<ResourceId> given;
	list<ResourceId> recv;
};