#include "CatanMap.h"
#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"

#include <algorithm>

void 
CatanMap::_create_land(void) {
	/* Creo los resource hex correspondientes */
	for (unsigned int ii = 0; ii < 5; ii++) {

		unsigned int hexCount;
		ResourceId hexId;

		/* Elijo que tipo de recurso asignar  */
		switch (ii) {
			case 0:
				hexCount = HILL_HEX_COUNT;
				hexId = ResourceId::HILL;
				break;
			case 1:
				hexCount = FOREST_HEX_COUNT;
				hexId = ResourceId::FOREST;
				break;
			case 2:
				hexCount = MOUNTAIN_HEX_COUNT;
				hexId = ResourceId::MOUNTAIN;
				break;
			case 3:
				hexCount = FIELD_HEX_COUNT;
				hexId = ResourceId::FIELD;
				break;
			case 4:
				hexCount = PASTURE_HEX_COUNT;
				hexId = ResourceId::PASTURES;
				break;
		}

		/* Ubicamos aleatoriamente */
		for (unsigned int i = 0; i < hexCount; i++) {
			ResourceHex* hex = new ResourceHex(hexId);
			landMap.push_back(hex);
		}
	}
}

void
CatanMap::_create_sea(void) {
	for (unsigned int i = 0; i < 6; i++) {
		SeaId id;

		switch (i) {
			case 0:
				id = SeaId::SHEEP;
				break;
			case 1:
				id = SeaId::NORMAL;
				break;
			case 2:
				id = SeaId::BRICK;
				break;
			case 3:
				id = SeaId::WOOD;
				break;
			case 4:
				id = SeaId::WHEAT;
				break;
			case 5:
				id = SeaId::STONE;
				break;
		}

		SeaHex* hex = new SeaHex(id);
		seaMap.push_back(hex);
	}
}

void
CatanMap::_create_robber(void) {
	robber = new Robber();
}

void
CatanMap::_destroy_land(void) {
	for (ResourceHex* hex : landMap) {
		if (hex) {
			delete hex;
		}
	}
}

void
CatanMap::_destroy_sea(void) {
	for (SeaHex* hex : seaMap) {
		if (hex) {
			delete hex;
		}
	}
}

void
CatanMap::_destroy_robber(void) {
	if (robber) {
		delete robber;
	}
}

void
CatanMap::_init_coords(void) {

}

CatanMap::
CatanMap(CatanGame* game) : FrameUI(MAP_ID, 0, 0) {

	/* Creo todos los objetos y elemetos */
	_create_land();
	_create_sea();
	_create_robber();

	/* Inicializo */
	_init_coords();
}

CatanMap::
~CatanMap(void) {
	 
	/* Destruyo todos los elementos */
	_destroy_land();
	_destroy_sea();
	_destroy_robber();
}

void
CatanMap::generateLand(void) {

	/* Genero la muestra de coordenadas dentro de un vector
	* con un orden aleatorio, luego de lo cual tomo cada uno
	* de esos elementos 
	*/
	vector<unsigned char> coords;
	for (unsigned char c = 'A'; c <= 'S'; c++)	coords.push_back(c);
	random_shuffle(coords.begin(), coords.end());

	/*
	* Itero el mapa de tierras y cada uno va tomando una posicion
	* dentro de la "bolsa" de coordenadas mezcladas
	*/
	for (ResourceHex* hex : landMap) {
		if (hex) {
			hex->place(coords.back()), coords.pop_back();
		}
	}
}

void
CatanMap::generateSea(void) {
	
	/* Genero una muestra de coordenadas para las piezas de mar
	* al azar
	*/
	vector<unsigned char> coords;
	for (unsigned char i = '0'; i <= '5'; i++) coords.push_back(i);
	random_shuffle(coords.begin(), coords.end());

	/* Le asigno de forma arbitraria cada una de las coordenadas
	* aleatorias a las piezas de mar
	*/
	for (SeaHex* hex : seaMap) {
		if (hex) {
			hex->place(coords.back()), coords.pop_back();
		}
	}
}

void
CatanMap::generateTokens(void) {
	vector<unsigned char> tokens;
	tokens.clear();

	/* Genero los numeros aleatorios y los mezclo de una forma arbitraria */
	tokens.push_back(2), tokens.push_back(12);
	for (unsigned char i = 3; i <= 11; i++) {
		if (i != 7) {
			tokens.push_back(i);
			tokens.push_back(i);
		}
	}
	random_shuffle(tokens.begin(), tokens.end());

	/* Asigno los tokens */
	for (ResourceHex* hex : landMap) {
		if (hex) {
			if (hex->getResource() == ResourceId::DESERT) {
				hex->setToken(0);
			}
			else {
				hex->setToken(tokens.back()), tokens.pop_back();
			}
		}
	}
}

bool
CatanMap::verifyMap(map<Coord, MapValue> gameMap) {
	bool verify;

	/*
	* Primero verifico que existan en la definicion, todos los puntos
	* del mapa, tanto de tierra como de mar, para lo cual
	* reviso que existan los elementos en el diccionario
	*/
	map<MapValue, unsigned int> counter;

	for (unsigned char i = MIN_SEA_COORD; i <= MAX_SEA_COORD; i++) {
		if (gameMap.find(i) == gameMap.end()) {
			return false;
		}

		if (counter.find(gameMap[i]) == counter.end()) {
			counter.insert(pair<MapValue, unsigned int>(gameMap[i], 1));
		}
		else {
			return false;
		}
	}
	/*
	* Luego compruebo que los valores mantengan una relacion
	* correcta de cantidades, segun lo establecido por las reglas
	* del juego Catan
	*/
	verify = (
		counter[(MapValue)SeaId::BRICK] == 1 &&
		counter[(MapValue)SeaId::WOOD] == 1 &&
		counter[(MapValue)SeaId::WHEAT] == 1 &&
		counter[(MapValue)SeaId::SHEEP] == 1 &&
		counter[(MapValue)SeaId::STONE] == 1 &&
		counter[(MapValue)SeaId::NORMAL] == 1
		);

	if (!verify)	return false;

	counter.clear();
	for (unsigned char i = MIN_LAND_COORD; i <= MAX_LAND_COORD; i++) {
		if (gameMap.find(i) == gameMap.end()) {
			return false;
		}

		if (counter.find(gameMap[i]) == counter.end()) {
			counter.insert(pair<MapValue, unsigned int>(gameMap[i], 1));
		}
		else {
			counter[gameMap[i]] += 1;
		}
	}
	verify = (
		counter[(MapValue)ResourceId::DESERT] == DESERT_HEX_COUNT &&
		counter[(MapValue)ResourceId::HILL] == HILL_HEX_COUNT &&
		counter[(MapValue)ResourceId::FOREST] == FOREST_HEX_COUNT &&
		counter[(MapValue)ResourceId::MOUNTAIN] == MOUNTAIN_HEX_COUNT &&
		counter[(MapValue)ResourceId::FIELD] == FIELD_HEX_COUNT &&
		counter[(MapValue)ResourceId::PASTURES] == PASTURE_HEX_COUNT
		);

	return verify;
}

bool
CatanMap::verifyTokens(map<Coord, unsigned char> tokens) {

	/*
	* Verifico que esten los tokens de todas las posiciones
	* y luego valido que los numeros esten en el rango que se
	* admite segun las reglas de Catan
	*/
	map<unsigned char, unsigned int> tokenCounter;

	for (unsigned char i = 3; i <= 11; i++) {
		if (i != 7) {
			tokenCounter.insert(pair<unsigned char, unsigned int>(i, 2));
		}
	}
	tokenCounter.insert(pair<unsigned char, unsigned int>(2, 1));
	tokenCounter.insert(pair<unsigned char, unsigned int>(12, 1));
	tokenCounter.insert(pair<unsigned char, unsigned int>(0, 1));

	for (unsigned char i = MIN_LAND_COORD; i <= MAX_LAND_COORD; i++) {

		if (tokens.find(i) == tokens.end()) {
			return false;
		}
		else {
			if (tokenCounter.find(tokens[i]) == tokenCounter.end()) {
				return false;
			}
			else if (tokenCounter[tokens[i]] > 0) {
				tokenCounter[tokens[i]] -= 1;
			}
			else if (tokenCounter[tokens[i]] == 0) {
				return false;
			}
		}
	}

	return true;
}

void
CatanMap::loadMap(map<Coord, MapValue> gameMap) {

	/* Creo una copia de la lista del mapa de tierras, para poder
	* ir determinando aquellos a los cuales ya les defini una coordenada
	* y aquellos a los que no. Hago lo mismo con los mares.
	*/
	list<ResourceHex*> landCopy = landMap;
	list<SeaHex*> seaCopy = seaMap;

	/* Itero el mapa recibido, tomando cada una de las coordenadas y
	* tipos de recursos, y asignandolo al siguiente disponible.
	*/
	for (auto hex : gameMap) {
		Coord coord = hex.first;
		if (coord.isSea()) {
			for (SeaHex* sea : seaCopy) {
				SeaId hexId = (SeaId)hex.second;
				if (sea->getDocks() == hexId) {
					sea->place(coord);
					seaCopy.remove(sea);
					break;
				}
			}
		}
		else if (coord.isLand()) {
			for (ResourceHex* land : landCopy) {
				ResourceId hexId = (ResourceId)hex.second;
				if (land->getResource() == hexId) {
					land->place(coord);
					landCopy.remove(land);
					break;
				}
			}
		}
	}
}

void
CatanMap::loadTokens(map<Coord, unsigned char> tokens) {
	/* Me muevo por todas las piezas de tierra ubicadas segun
	* segun sus coordenadas, a cada una, le asigno correspondientemente
	* los valores de los tokens
	*/
	for (ResourceHex* land : landMap) {

		/* Busco la coordenada en el mapa y luego tomo el valor
		* del token y lo asigno al land
		*/
		unsigned char token = tokens[land->getCoord()];
		land->setToken(token);
	}
}

void
CatanMap::build(Building* building, Coord coord) {
	/* Ubico la posicion del building en la pantalla
	* y su locacion logica dentro del juego
	*/
	position_t pos = screenCoords[coord];
	building->build(coord, pos.x, pos.y, pos.info);

	/* Agrego el building al conjunto de construcciones
	* realizadas
	*/
	builtMap.push_back(building);
}

void
CatanMap::demolish(Building* building) {
	/* Ubico la posicion del building en la pantalla
	* y su locacion logica dentro del juego
	*/
	building->demolish();

	/* Elimino la construccion dentro de la lista de 
	* elementos o componentes construidos 
	*/
	builtMap.remove(building);
}

list<Building*>
CatanMap::buildings(void) {
	return builtMap;
}

void
CatanMap::moveRobber(Coord coord) {
	/* Muevo el robber a la nueva ubicacion, pero previo a ello
	* busco la posicion en pixeles dentro de la ventana segun
	* la configuracion misma.
	*/
	position_t pos = screenCoords[coord];
	robber->move(coord, pos.x, pos.y);
}

Coord
CatanMap::robberPosition(void) {
	return robber->getCoord();
}

list<ResourceHex*>
CatanMap::lands(void) {
	return landMap;
}

ResourceHex*
CatanMap::land(Coord coord) {
	for (ResourceHex* hex : landMap) {
		if (hex) {
			if (hex->getCoord() == coord) {
				return hex;
			}
		}
	}
}

list<SeaHex*>
CatanMap::seas(void) {
	return seaMap;
}

SeaHex* 
CatanMap::sea(Coord coord) {
	for (SeaHex* hex : seaMap) {
		if (hex) {
			if (hex->getCoord() == coord) {
				return hex;
			}
		}
	}
}

map<Coord, position_t>
CatanMap::screen(void) {
	return screenCoords;
}