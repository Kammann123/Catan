#pragma once

#include "NetworkPacket.h"

#include <map>

using namespace std;

/*
* MapPacket
* Paquete de datos con la informacion de la disposicion del mapa.
*/
class MapPacket : public NetworkPacket {

public:
	/*
	* Constructores y destructores
	*/
	MapPacket(void);
	virtual ~MapPacket();

	/*
	* SetMapValue
	* Establece el valor de una celda del mapa.
	* Esta puede ser mar o tierra, no obstante,
	* en caso de ser una coordenada invalida, pues se toman
	* como mar: 0, 1, 2, 3, 4, 5, 6 o tierra: A, ..., S
	* se devolvera False. En caso contrario, sera True.
	*/
	bool setMapValue(unsigned char coord, MapValue value);

	/*
	* getMap
	* Devuelve el mapa completo
	*/
	map<unsigned char, MapValue>& getMap(void);
	
private:
	map<unsigned char, MapValue> gameMap;
};