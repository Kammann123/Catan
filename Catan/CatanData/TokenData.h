#pragma once

#include "CatanData.h"
#include "../CatanGame/Coord.h"

#include <map>

using namespace std;

/*
* TokenData
* Implementacion de informacion con los tokenes del mapa
*/
class TokenData : public CatanData {
public:
	/* Constructores */
	TokenData(map<Coord, unsigned char> tokens);
	TokenData(void);

	/* Setters y getters */
	bool setToken(Coord coord, unsigned char token);
	unsigned char getToken(unsigned char coord);
	map<Coord, unsigned char>& getTokens(void);
private:
	map<Coord, unsigned char> tokens;
};