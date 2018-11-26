#pragma once

#include <string>
#include <vector>
#include <map>
#include <exception>

using namespace std;

#define MIN_SEA_COORD	'0'
#define MAX_SEA_COORD	'5'

#define MIN_LAND_COORD	'A'
#define MAX_LAND_COORD	'S'

extern const string internalDots[22];
extern const string externalDots[30];
extern const string internalEdges[40];
extern const string externalEdges[30];

/*
* Coord
* Modelizacion de una coordenada del juego Catan.
*
* Consideracion de las reglas para definir puntos y lineas dentro del mapa:
*	+ En la tierra, los puntos son de 3 coordenadas, interseccion entre hexagonos.
*	+ En la costa, los puntos siguen siendo interseccion entre piezas, pero pueden ser 3 o 2.
*	+ En la tierra, las lineas son de 2 coordenadas. Interseccion entre hexagonos.
*	+ En la costa, las lineas son de 3 coordeandas, segun los terrenos que la linea toca.
*
*/
class Coord {
public:

	enum Type : unsigned int { DOT, EDGE, LAND, SEA, NONE };

	/* Constructores */
	Coord();
	Coord(string coords);
	Coord(string coords, Type type);
	Coord(const Coord& copy);
	Coord(unsigned char coord);
	Coord(Coord& c1, Coord& c2);
	Coord(vector<unsigned char> coord);

	/* Sobrecarga de operadores */
	bool operator<(const Coord& coord) const;
	bool operator<=(const Coord& coord) const;
	bool operator>(const Coord& coord) const;
	bool operator>=(const Coord& coord) const;
	bool operator==(Coord copy);
	bool operator==(string coordsCmp);
	bool operator==(unsigned char coord);

	unsigned char operator[](unsigned int index);

	Coord& operator=(unsigned char coord);
	Coord& operator=(string coords);
	Coord& operator=(Coord coords);

	Coord& operator+=(unsigned char coord);
	Coord& operator+=(string coords);
	Coord& operator+=(Coord coords);

	/* Definicion de los parametros de la coordenada */
	void setCoord(string coords, Type type);
	void setCoord(unsigned char coord);
	void forceEdge(void);
	void forceDot(void);

	string getCoords(void);

	string::iterator begin(void);
	string::iterator end(void);
	size_t size(void);

	/* 
	* Metodos de validacion y verificacion de la coordenada
	* segun la coordenada, o con respecto a otras coordenadas.
	*/
	bool isSea(void);
	bool isLand(void);
	bool isDot(void);
	bool isEdge(void);
	bool nearCoast(void);
	
	/*
	* isVertexOf
	* Devuelve true validando si la coordenada objeto es vertice
	* de los parametros pasados como una nueva coordenada, donde se espera
	* que esto recibido esa de tipo Land, pues no podria ser sino un vertex.
	*/
	bool isVertexOf(Coord coord);
	bool isVertexOf(unsigned char coord);

	/*
	* isEdgeOf
	* Devuelve true validando si la coordenada pasada al objeto es un vertice
	* extremo de la coordenada actual, donde se entiende que para que pueda ser
	* posible, primero la coordenada actual debe ser de tipo Edge.
	*/
	bool isEdgeOf(Coord& coord);
	bool isEdgeOf(unsigned char coord);

	/*
	* edgeContinuity
	* Devuelve true validando si la coordenada pasada al metodo es un Edge
	* continuo al Edge de la coordenada actual, asumiendo que ambos son de tal tipo
	* en cuyo caso contrario, sera false.
	*/
	bool edgeContinuity(Coord& coord);
	bool edgeContinuity(unsigned char coord);

	/*
	* isAdjacentDot
	* Devuelve true si la coordenada actual y la que se pasa a evaluar
	* son ambas de tipo Dot y son adyacentes entre si.
	*/
	bool isAdjacentDot(Coord& coord);
	bool isAdjacentDot(unsigned char coord);

private:

	bool _has_numbers(void);
	bool _has_letters(void);
	bool _has(unsigned char coord);

	unsigned int _count_numbers(void);
	void _handle_repetition(void);
	void _handle_repetition_intersection(void);

	void _verify_value(void);
	void _verify_type(void);

	bool _is_valid_edges(void);
	bool _is_valid_land(void);
	bool _is_valid_dot(void);
	bool _is_valid_sea(void);

	void _update_coord(void);

	string coords;
	Type type;
};