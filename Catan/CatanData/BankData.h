#pragma once

#include "CatanData.h"
#include "../CatanGame/ResourceCard.h"

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
	BankData(list<ResourceCard*> given, list<ResourceId> recv);
	BankData();

	/*
	* Getters y setters
	*/
	void addGiven(ResourceId res);
	void addReceived(ResourceId res);
	list<ResourceId>& getGiven(void);
	list<ResourceId>& getRecv(void);

	void addGiven(ResourceCard* res);
	list<ResourceCard*>& getGivenCards(void);

	/* Metodos de verificacion de tipo de transaccion */
	bool isBankTrade(void);
	bool isDockTrade(void);
	bool hasLocal(void);
	bool hasRemote(void);

private:
	list<ResourceId> given;
	list<ResourceId> recv;

	list<ResourceCard*> givenCard;
};