#pragma once

#include "CatanData.h"

#include "../CatanGame/Coord.h"

#include <map>

using namespace std;

/*
* MapData
* Implementacion con la informacion del mapa en su forma de estar ordenado
*/
class MapData : public CatanData {
public:
	/* Constructores */
	MapData(map<Coord, MapValue> m);
	MapData();

	/* Setters y getters */
	bool setMap(Coord coord, MapValue value);
	map<Coord, MapValue>& getMap(void);
private:
	map<Coord, MapValue> gameMap;
};