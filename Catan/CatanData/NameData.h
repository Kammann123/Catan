#pragma once

#include "CatanData.h"

#include <string>

using namespace std;

/*
* NameData
* Implementacion con la informacion del nombre de un jugador.
*/
class NameData : public CatanData {
public:
	/* Constructor */
	NameData(string name);
	NameData();

	/* Setters y getters */
	void setName(string name);
	void setName(unsigned char name);
	string getName(void);
private:
	string name;
};