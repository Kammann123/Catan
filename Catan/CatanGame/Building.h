#pragma once

#include "../CatanData/BuildingData.h"
#include "Coord.h"

#include <string>
#include <list>

using namespace std;

#define BUILDING_NOT_PLACED	"FFF"

enum class PlayerId;

/*
* Building
* Clase de construccion del juego, con el tipo, posicion o ubicacion,
* y usuario a quien pertenece.
*/
class Building {
public:
	/*
	* Constructor
	*/
	Building(Coord place, PlayerId player, BuildingType type);
	Building(PlayerId player, BuildingType type);
	Building(BuildingType type);

	/*
	* getPlace()
	* Devuelve las coordenadas de la construcción
	*/
	Coord getPlace(void);

	/*
	* getPlayer
	* Devuelve el jugador al que pertence la construccion
	*/
	PlayerId getPlayer(void);

	/*
	* getType
	* Devuelve el tipo de onstruccion
	*/
	BuildingType getType(void);

	/*
	* setPlace
	* Define la posicion de la construccion
	*/
	void setPlace(Coord place);

	/*
	* setPlayer
	* Define a que jugador pertenece
	*/
	void setPlayer(PlayerId player);

	/*
	* addNeighbour/removeNeighbour
	* Agrego/Quito un vecino contiguo a la construccion, para ir armando
	* las conexiones del grafo de caminos y construcciones
	*/
	void addNeighbour(list<Building*> buildings);
	void addNeighbour(Building* building);
	void removeNeighbour(Building* building);
	void removeNeighbour(void);

	/*
	* getNeighbours
	* Devuelve la lista de vecinos, para ir visitandolos a cada
	* uno de ellos y llevar la cuenta de las visitas
	*/
	list<Building*> getNeighbours(void);

	/*
	* hasNeighbours
	* Devuelve true si el building tiene vecinos agregados
	*/
	bool hasNeighbours(void);

	/*
	* wasVisited
	* Consulta si ya fue visitada la construccion en particular
	*/
	bool wasVisited(void);

	/*
	* visit
	* Marca el estado de la visita en esta construccion
	*/
	void visit(bool status = true);

private:
	list<Building*> neighbours;
	bool visited;
	Coord place;
	BuildingType type;
	PlayerId player;
};