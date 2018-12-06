#pragma once

#include "CatanData.h"

#include "../CatanGame/Coord.h"

#include <string>

using namespace std;

/*
* BuildingType
* Tipos de construcciones del juego
*/
enum class BuildingType : unsigned int { ROAD, SETTLEMENT, CITY };

/*
* BuildingData
* Implementacion de la informacion de una nueva construccion en el juego
*/
class BuildingData : public CatanData {
public:

	/* Constructor */
	BuildingData(BuildingType type, Coord coords);
	BuildingData();

	/* Getter y setters */
	bool setCoords(Coord coord);
	void setType(BuildingType type);
	Coord& getCoords(void);
	BuildingType getType(void);

protected:
	Coord coords;
	BuildingType type;
};