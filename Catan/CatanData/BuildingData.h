#pragma once

#include "CatanData.h"

#include <string>

using namespace std;

/*
* BuildingType
* Tipos de construcciones del juego
*/
enum class BuildingType : unsigned int { SETTLEMENT, ROAD, CITY };

/*
* BuildingData
* Implementacion de la informacion de una nueva construccion en el juego
*/
class BuildingData : public CatanData {
public:

	/* Constructor */
	BuildingData(BuildingType type, string coords);
	BuildingData();

	/* Getter y setters */
	bool setCoords(string coords);
	bool setCoords(unsigned char coord);
	void setType(BuildingType type);
	string getCoords(void);
	BuildingType getType(void);

private:
	string coords;
	BuildingType type;
};