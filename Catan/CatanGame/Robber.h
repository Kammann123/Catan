#pragma once

/*
* Robber
* La mejor clase del mundo para el Robber del juego.
*/
class Robber {
public:
	/* Constructor */
	Robber(unsigned char coord);
	Robber();

	/* 
	* getCoord
	* Devuelve la posicion actual del robber
	*/
	unsigned char getCoord(void) const;

	/*
	* setCoord
	* Mueve el robber de posicion
	*/
	void setCoord(unsigned char coord);

private:
	unsigned char coord;
};