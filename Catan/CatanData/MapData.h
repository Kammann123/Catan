#pragma once

#include "CatanData.h"

#include <map>

using namespace std;

/*
* MapData
* Implementacion con la informacion del mapa en su forma de estar ordenado
*/
class MapData : public CatanData {
public:
	/* Constructores */
	MapData(map<unsigned char, MapValue> m);
	MapData();

	/* Setters y getters */
	bool setMap(unsigned char coord, MapValue value);
	map<unsigned char, MapValue>& getMap(void);
private:
	map<unsigned char, MapValue>& gameMap;
};