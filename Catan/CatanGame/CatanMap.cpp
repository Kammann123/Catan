#include "CatanMap.h"
#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"

#include <algorithm>

#define _0_SEA_ROTATION 180
#define _1_SEA_ROTATION 240
#define _2_SEA_ROTATION 300
#define _3_SEA_ROTATION 0
#define _4_SEA_ROTATION 60
#define _5_SEA_ROTATION 120

#define MAP_ALPHA 300
#define MAP_BETA 60
#define MAP_VERTICAL 90
#define MAP_NONE 0

double
positionDistance(position_t p1, position_t p2) {
	double distance = 0;
	distance = sqrt(pow((p2.y - p1.y), 2) + pow((p2.x - p1.x), 2));
	return distance;
}

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

	/* Agrego el terreno desierto */
	ResourceHex* hex = new ResourceHex(ResourceId::DESERT);
	landMap.push_back(hex);
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
	robber = new Robber(this);
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
	edgeCoords = {
		/* Sides (Roads) */
		{ "0A5",{ 211.71,73,MAP_ALPHA } },{ "0AB",{ 261.71,73,MAP_BETA } },{ "0BA",{ 312.55,73,MAP_ALPHA } },{ "0BC",{ 363.05,73,MAP_BETA } },{ "0C",{ 413.21,73,MAP_ALPHA } },{ "1C0",{ 463.21,73,MAP_BETA } },{ "5A",{ 187.42,117.165,MAP_VERTICAL } },{ "AB",{ 287.42,117.165,MAP_VERTICAL } },{ "BC",{ 388.42,117.165,MAP_VERTICAL } },{ "1CG",{ 488.42,117.165,MAP_VERTICAL } },
		{ "5DA",{ 161.59,161.335,MAP_ALPHA } },{ "AD",{ 211.71,161.335,MAP_BETA } },{ "AE",{ 261.71,161.335,MAP_ALPHA } },{ "BE",{ 312.55,161.335,MAP_BETA } },{ "BF",{ 363.05,161.335,MAP_ALPHA } },{ "CF",{ 413.21,161.335,MAP_BETA } },{ "CG",{ 463.21,161.335,MAP_ALPHA } },{ "1GC",{ 513.55,161.335,MAP_BETA } },{ "5DH",{ 135.75,204.835,MAP_VERTICAL } },{ "DE",{ 236,204.835,MAP_VERTICAL } },
		{ "EF",{ 337.67,204.835,MAP_VERTICAL } },{ "FG",{ 438,204.835,MAP_VERTICAL } },{ "1GL",{ 538.67,204.835,MAP_VERTICAL } },{ "5HD",{ 110.21,248.335,MAP_ALPHA } },{ "DH",{ 161.59,248.335,MAP_BETA } },{ "DI",{ 211.71,248.335,MAP_ALPHA } },{ "EI",{ 261.71,248.335,MAP_BETA } },{ "EJ",{ 312.55,248.335,MAP_ALPHA } },{ "FJ",{ 363.05,248.335,MAP_BETA } },{ "FK",{ 413.21,248.335,MAP_ALPHA } },
		{ "GK",{ 463.21,248.335,MAP_BETA } },{ "GL",{ 513.55,248.335,MAP_ALPHA } },{ "1L",{ 563.55,248.335,MAP_BETA } },{ "5H4",{ 84.67,292.67,MAP_VERTICAL } },{ "HI",{ 187.42,292.67,MAP_VERTICAL } },{ "IJ",{ 287.42,292.67,MAP_VERTICAL } },{ "JK",{ 388.42,292.67,MAP_VERTICAL } },{ "KL",{ 488.42,292.67,MAP_VERTICAL } },{ "2L1",{ 588.42,292.67,MAP_VERTICAL } },{ "H4",{ 110.21,337,MAP_BETA } },
		{ "HM",{ 161.59,337,MAP_ALPHA } },{ "IM",{ 211.71,337,MAP_BETA } },{ "IN",{ 261.71,337,MAP_ALPHA } },{ "JN",{ 312.55,337,MAP_BETA } },{ "JO",{ 363.05,337,MAP_ALPHA } },{ "KO",{ 413.21,337,MAP_BETA } },{ "KP",{ 463.21,337,MAP_ALPHA } },{ "LP",{ 513.55,337,MAP_BETA } },{ "2LP",{ 563.55,337,MAP_ALPHA } },{ "4MH",{ 135.75,380.165,MAP_VERTICAL } },
		{ "MN",{ 236,380.165,MAP_VERTICAL } },{ "NO",{ 337.67,380.165,MAP_VERTICAL } },{ "OP",{ 438,380.165,MAP_VERTICAL } },{ "2PL",{ 538.67,380.165,MAP_VERTICAL } },{ "4MQ",{ 161.59,423.5,MAP_BETA } },{ "MQ",{ 211.71,423.5,MAP_ALPHA } },{ "NQ",{ 261.71,423.5,MAP_BETA } },{ "NR",{ 312.55,423.5,MAP_ALPHA } },{ "OR",{ 363.05,423.5,MAP_BETA } },{ "OS",{ 413.21,423.5,MAP_ALPHA} },
		{ "PS",{ 463.21,423.5,MAP_BETA } },{ "2PS",{ 513.55,423.5,MAP_ALPHA } },{ "4QM",{ 187.42,466.665,MAP_VERTICAL } },{ "QR",{ 287.42,466.665,MAP_VERTICAL } },{ "RS",{ 388.42,466.665,MAP_VERTICAL } },{ "2S",{ 488.42,466.665,MAP_VERTICAL } },{ "4Q3",{ 211.71,510.5,MAP_BETA } },{ "3Q",{ 261.71,510.5,MAP_ALPHA } },{ "3RQ",{ 312.55,510.5,MAP_BETA } },{ "3RS",{ 363.05,510.5,MAP_ALPHA } },
		{ "3SR",{ 413.21,510.5,MAP_BETA } },{ "3S2",{ 463.21,510.5,MAP_ALPHA } }
	};

	dotCoords = {
		/* Vertex (Settlements/Cities) */
		{ "0A",{ 236,58.67,MAP_NONE } },{ "0B",{ 337.67,58.67,MAP_NONE } },{ "01C",{ 438,58.67,MAP_NONE } },{ "05A",{ 187.42,87.33,MAP_NONE } },{ "0AB",{ 287.42,87.33,MAP_NONE } },{ "0BC",{ 388.42,87.33,MAP_NONE } },{ "1C",{ 488.42,87.33,MAP_NONE } },{ "5AD",{ 187.42,147,MAP_NONE } },{ "ABE",{ 287.42,147,MAP_NONE } },{ "BCF", {388.42,147,MAP_NONE} },
		{ "1CG",{ 488.42,147,MAP_NONE} },{ "5D",{ 135.75,175.67,MAP_NONE } },{ "ADE",{ 236,175.67,MAP_NONE } },{ "BEF",{ 337.67,175.67,MAP_NONE } },{ "CFG",{ 438,175.67,MAP_NONE } },{ "1G",{ 538.67,175.67,MAP_NONE } },{ "5DH",{ 135.75,234,MAP_NONE } },{ "DEI",{ 236,234,MAP_NONE } },{ "EFJ",{ 337.67,234,MAP_NONE } },{ "FGK",{ 438,234,MAP_NONE } },
		{ "5H", { 84.67,262.67,MAP_NONE} },{ "DHI",{187.42,262.67,MAP_NONE} },{"EIJ",{287.42,262.67,MAP_NONE}},{"FJK",{388.42,262.67,MAP_NONE}}, {"1GL",{538.67,234,MAP_NONE}},
		{ "GKL",{ 488.42,262.67,MAP_NONE } },{ "12L",{ 588.42,262.67,MAP_NONE } },{ "45H",{ 84.67,322.67,MAP_NONE } },{ "HIM",{ 187.42,322.67,MAP_NONE } },{ "IJN",{ 287.42,322.67,MAP_NONE } },{ "JKO",{ 388.42,322.67,MAP_NONE } },{ "KLP",{ 488.42,322.67,MAP_NONE } },{ "2L",{ 588.42,322.67,MAP_NONE } },{ "4HM",{ 135.75,351.33,MAP_NONE } },{ "IMN",{ 236,351.33,MAP_NONE } },
		{ "JNO",{ 337.67,351.33,MAP_NONE } },{ "KOP",{ 438,351.33,MAP_NONE } },{ "2LP",{ 538.67,351.33,MAP_NONE } },{ "4M",{ 135.75,409,MAP_NONE } },{ "NMQ",{ 236,409,MAP_NONE } },{ "NOR",{ 337.67,409,MAP_NONE } },{ "OPS",{ 438,409,MAP_NONE } },{ "2P",{ 538.67,409,MAP_NONE } },{ "4MQ",{ 187.42,438,MAP_NONE } },{ "NQR",{ 287.42,438,MAP_NONE } },
		{ "ORS",{ 388.42,438,MAP_NONE } },{ "2PS",{ 488.42,438,MAP_NONE } },{ "4Q",{ 187.42,495.33,MAP_NONE } },{ "MQR",{ 287.42,495.33,MAP_NONE } },{ "3RS",{ 388.42,495.33,MAP_NONE } },{ "23S",{ 488.42,495.33,MAP_NONE } },{ "34Q",{ 236,525.67,MAP_NONE } },{ "3R",{ 337.67,525.67,MAP_NONE } },{ "3S",{ 438,525.67,MAP_NONE } }
	};

	screenCoords = {
		/* Hexagons */
		{ "A",{ 236,117.165,MAP_NONE } },{ "B",{ 337.67,117.165,MAP_NONE } },{ "C",{ 438,117.165,MAP_NONE } },{ "D",{ 187.42,204.835,MAP_NONE } },{ "E",{ 287.42,204.835,MAP_NONE } },{ "F",{ 388.42,204.835,MAP_NONE } },{ "G",{ 488.42,204.835,MAP_NONE } },{ "H",{ 135.75,292.67,MAP_NONE } },{ "I",{ 236,292.67,MAP_NONE } },{ "J",{ 337.67,292.67 } },
		{ "K",{ 438,292.67,MAP_NONE } },{ "L",{ 538.67,292.67,MAP_NONE } },{ "M",{ 187.42,380.165,MAP_NONE } },{ "N",{ 287.42,380.165,MAP_NONE } },{ "O",{ 388.42,380.165,MAP_NONE } },{ "P",{ 488.42,380.165,MAP_NONE } },{ "Q",{ 236,466.665,MAP_NONE } },{ "R",{ 337.67,466.665,MAP_NONE } },{ "S",{ 438,466.665,MAP_NONE } },
		/* Seas */
		{ "0",{ 301,41,_0_SEA_ROTATION } },{ "1",{ 534,131,_1_SEA_ROTATION } },{ "2",{ 575,378,_2_SEA_ROTATION } },{ "3",{ 378.5,538.25,_3_SEA_ROTATION } },{ "4",{ 146,449.75,_4_SEA_ROTATION } },{ "5",{ 107,201.75,_5_SEA_ROTATION } }
	};
}

CatanMap::
CatanMap(CatanGame* game) : FrameUI(MAP_ID, 0, 0) {
	this->setUIDestroy(false);

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

			if (hex->getResource() == ResourceId::DESERT) {
				moveRobber(hex->getCoord());
			}
		}
	}

	notifyObservers();
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

	notifyObservers();
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

	notifyObservers();
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

					if (hexId == ResourceId::DESERT) {
						moveRobber(coord);
					}
					break;
				}
			}
		}
	}

	notifyObservers();
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
	position_t pos;
	switch (building->getType()) {
		case BuildingType::SETTLEMENT: case BuildingType::CITY:
			pos = dotCoords[coord.getCoords()];
			break;
		case BuildingType::ROAD:
			pos = edgeCoords[coord.getCoords()];
			break;
	}
	building->build(coord, pos.x + x, pos.y + y, pos.info);

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
	position_t pos = screenCoords[coord.getCoords()];
	robber->move(coord, pos.x + x, pos.y + y);
}

Coord
CatanMap::robberPosition(void) {
	return robber->getCoord();
}

Robber*
CatanMap::getRobber(void) {
	return robber;
}

map<Coord, MapValue> 
CatanMap::getMap(void) {
	map<Coord, MapValue> catanMap;	

	for (ResourceHex* land : landMap) {
		catanMap.insert(pair<Coord, MapValue>(land->getCoord(), (MapValue)land->getResource()));
	}
	for (SeaHex* sea : seaMap) {
		catanMap.insert(pair<Coord, MapValue>(sea->getCoord(), (MapValue)sea->getDocks()));
	}

	return catanMap;
}

map<Coord, unsigned char>
CatanMap::getTokens(void) {
	map<Coord, unsigned char> tokens;

	for (ResourceHex* land : landMap) {
		tokens.insert(pair<Coord, unsigned char>(land->getCoord(), land->getToken()));
	}

	return tokens;
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
	return nullptr;
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
	return nullptr;
}

map<string, position_t> 
CatanMap::screenHexCoords(void) {
	return screenCoords;
}

map<string, position_t>
CatanMap::screenDotCoords(void) {
	return dotCoords;
}

map<string, position_t>
CatanMap::screenEdgeCoords(void) {
	return edgeCoords;	
}