#pragma once

#include "MouseUI.h"

/*
* TextUI
* Entrada de texto que hereda de MouseUI para tener la posibilidad
* de ser utilizada con el mouse tambien. Se define para ella un
* TextController especifico para entradas por KeyBoard.
*/
class TextUI : public MouseUI {
public:

	/*
	* Mode - Modos de funcionamiento del TextUI, permite definir
	* que es lo que aceptamos que ingrese al mismo.
	*/
	enum Mode : unsigned int { NUMBER, LETTER, BOTH, EVERYTHING };

	/*
	* TextUI
	* Se construye con el modo que por defecto permite que entre
	* cualquier cosa al mismo.
	*/
	TextUI(string id, size_t size, Mode mode = EVERYTHING);
	~TextUI();

	/*
	* Acceso, lectura y modificacion del contenido
	*/
	void setText(const char* value);
	void setText(string value);
	void setMode(Mode mode);
	string getText(void);
	Mode getMode(void);

	/*
	* append
	* Agregar al final del elemento validando
	* que este disponible ese modo en la configuracion del TextUI
	*/
	void append(unsigned char value);
	void append(string value);
	void append(const char* value);

	/*
	* remove
	* Remueve el ultimo caracter
	*/
	void remove(void);

	/*
	* clear
	* Limpia el contenido
	*/
	void clear(void);

	/*
	* Configuracion de callbacks
	*/
	void setEnterAction(Action enter);

	/*
	* Ejecucion de callbacks
	*/
	void enter(void*);

private:

	/*
	* Rutinas de control de valores
	*/
	bool _is_number(unsigned char value);
	bool _is_letter(unsigned char value);

	Mode mode;
	string text;
	size_t size;

	/* Callbacks de ejecucion */
	Action onEnter;
};