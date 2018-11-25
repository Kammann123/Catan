#include "CatanData.h"

#define IS(value, compareValue, cast) ((value) == (cast)(compareValue))

/* Funciones */
bool isMapValue(unsigned char value) {

	return isSeaValue(value) || isResourceValue(value);
}

bool isSeaValue(unsigned char value) {

	return (
		IS(value, SeaId::NORMAL, unsigned char) ||
		IS(value, SeaId::WHEAT, unsigned char) ||
		IS(value, SeaId::SHEEP, unsigned char) ||
		IS(value, SeaId::BRICK, unsigned char) ||
		IS(value, SeaId::STONE, unsigned char) ||
		IS(value, SeaId::WOOD, unsigned char)
		);
}

bool isResourceValue(unsigned char value) {

	return (
		IS(value, ResourceId::FOREST, unsigned char) ||
		IS(value, ResourceId::HILL, unsigned char) ||
		IS(value, ResourceId::MOUNTAIN, unsigned char) ||
		IS(value, ResourceId::FIELD, unsigned char) ||
		IS(value, ResourceId::PASTURES, unsigned char) ||
		IS(value, ResourceId::DESERT, unsigned char)
		);
}

bool isValidToken(unsigned char value) {

	if (value == 0 || (value >= 2 && value <= 6) || (value >= 8 && value <= 12)) {
		return true;
	}
	else {
		return false;
	}
}

bool isDevCard(unsigned char value) {

	return(
		IS(value, DevCardId::KNIGHT, unsigned char) ||
		IS(value, DevCardId::VICTORY_POINT, unsigned char) ||
		IS(value, DevCardId::ROAD_BUILD, unsigned char) ||
		IS(value, DevCardId::MONOPOLY, unsigned char) ||
		IS(value, DevCardId::YEARS_OF_PLENTY, unsigned char)
		);
}

bool isValidDice(unsigned char value) {
	return (value >= '1' && value <= '6');
}

bool isMapPosition(unsigned char value) {
	return (value >= 'A' && value <= 'S');
}

bool isSeaPosition(unsigned char value) {
	return (value >= '0' && value <= '5');
}

bool matchCoords(string str1, string str2)
{
	bool ret = true;

	if (str1.length() == str2.length()) // ambos strings deben tener la misma longitud
	{
		for (int i = 0; i < str1.length(); i++) // para cada caracter del string1
		{
			if (str2.find(str1.c_str()[i]) == string::npos) // si no lo encuentro, entonces las coordenadas no son iguales
			{
				ret = false; // cambio el parámetro de return
				break; // y finalizo el barrido, porque ya las coordenadas no son iguales

			}
		}

	}

	else
	{
		ret = false;
	}

	return ret;
}
