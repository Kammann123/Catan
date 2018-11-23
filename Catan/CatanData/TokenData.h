#pragma once

#include "CatanData.h"

#include <map>

using namespace std;

/*
* TokenData
* Implementacion de informacion con los tokenes del mapa
*/
class TokenData : public CatanData {
public:
	/* Constructores */
	TokenData(map<unsigned char, unsigned char> tokens);
	TokenData(void);

	/* Setters y getters */
	bool setToken(unsigned char coord, unsigned char token);
	unsigned char getToken(unsigned char coord);
	map<unsigned char, unsigned char>& getTokens(void);
private:
	map<unsigned char, unsigned char> tokens;
};