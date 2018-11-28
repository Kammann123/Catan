#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "MVC/Controller.h"
#include "MVC/Observer.h"
#include "MVC/Subject.h"
#include <string>

using namespace std;

enum class FrameState {IDLE, FOCUSED, SELECTED};

typedef void(*callback)(void*);
using pixel = unsigned int;

typedef struct 
{
	double x;
	double y;

}ImageCoords_t;



class SelectionFeature {
public:
	/* Constructor / Destructor */
	SelectionFeature(ALLEGRO_BITMAP* selectedBitmap_, ALLEGRO_BITMAP* focusedBitmap_, callback doIfSelected_, callback doIfFocused_);
	~SelectionFeature();

	/* Setters */
	void toggleSelection(void);
	void setFocus(bool newState);
	void setSelectedBmap(ALLEGRO_BITMAP* newBitmap);
	void setFocusedBitmap(ALLEGRO_BITMAP* newBitmap);

	/* Getters */
	bool isSelected(void);
	bool isFocused(void);

private:
	ALLEGRO_BITMAP* selectedBitmap;
	ALLEGRO_BITMAP* focusedBitmap;
	bool selected;
	bool focused;
	callback doIfSelected;
	callback doIfFocused;
};


class TextField {
public:
	/* Constructor / Destructor */
	TextField(pixel width_, pixel height_, ALLEGRO_FONT* font_, ALLEGRO_COLOR boxColor_, callback doIfEnter_);
	~TextField();

	void addChar(unsigned char newChar);
	void deleteChar(void);
	void eraseAll(void);
	void toggleSelection(void);
	void clearSelection(void);

	/* Getters */
	bool isSelected(void);
	unsigned int getWidth(void);
	unsigned int getHeight(void);
	string getText(void);

	/* Setters */

private:
	unsigned int width;
	unsigned int height;
	bool selected;
	string text;
	ALLEGRO_COLOR boxColor;
	ALLEGRO_FONT* font;
	callback doIfEnter;

};


/* Base Class */
class ImageWidget{

public:
	/* Constructor / Destructor */
	ImageWidget(ALLEGRO_DISPLAY* display_, ALLEGRO_BITMAP* bitmap_, ImageCoords_t coords_);
	~ImageWidget();

	 /* Getters */
	ALLEGRO_BITMAP* getBitmap(void);
	ALLEGRO_DISPLAY* getDisplay(void);
	ImageCoords_t getCoords(void);

			
	/* Setters */
	void setBitmap(ALLEGRO_BITMAP* newBitmap);
	void setDisplay(ALLEGRO_DISPLAY* newDisplay);
	void setCoords(ImageCoords_t newCoords);
	void setCoords(double x, double y);

private:
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_DISPLAY* display;
	ImageCoords_t coords;
};


class Label {
public:
	/* Constructor / Destructor */
	Label(ALLEGRO_FONT* font_, string initialText);
	~Label();

	void eraseAll(void);


	/* Getters */
	string getText(void);

	/* Setters */
	void setText(string text_);

private:
	string text;
	ALLEGRO_FONT* font;

};

/************************************************************************************************************************************************/
/************************************************************************************************************************************************/
/************************************************************************************************************************************************/


											/*  NUEVA IMPLEMENTACION */
/*
* Clase FrameUI
* Clase base para un widget (modelo)
*/

class FrameUI : public Subject 
{
public:
		
	FrameUI(unsigned int width_, unsigned int height_, ImageCoords_t coords, callback onClick_, callback onExit_, callback onRelease_, callback onEnter);
	FrameUI(unsigned int width_, unsigned int height_, double x_, double y_, callback onClick_, callback onExit_, callback onRelease_, callback onEnter);
	~FrameUI();

	/* Getters */

	unsigned int getWidth(void);
	unsigned int getHeigth(void);
	ImageCoords_t getCoords(void);
	FrameState getState(void);
	callback getOnClickCallback(void);
	callback getOnExitCallback(void);
	callback getOnReleaseCallback(void);
	callback getOnEnterCallback(void);

	/* Setters */

	void setWidth(unsigned int newWidth);
	void setHeight(unsigned int newHeigth);
	void setCoords(ImageCoords_t newCoords);
	void setXCoord(unsigned int newX);
	void setYCoord(unsigned int newY);
	void setState(FrameState newState);
	void setOnClickCallback(callback newCallback);
	void setOnEnterCallback(callback newCallback);
	void setOnExitCallback(callback newCallback);
	void setOnReleaseCallback(callback newCallback);


	
private:

	unsigned int width;
	unsigned int height;
	ImageCoords_t coords;
	FrameState	currentState;
	callback onClick;
	callback onExit;
	callback onRelease;
	callback onEnter;
	

};


class FrameUIController: public Controller
{
public:

	FrameUIController(FrameUI& model_);
	~FrameUIController();

	/*
	* parseMouseEvent()
	* Parser de un evento de mouse de Allegro
	*/
	void parseMouseEvent(ALLEGRO_EVENT* ev_);
	void parseKeyboardEvent(ALLEGRO_EVENT* ev_);

private:
	FrameUI& model;
	//FrameUIView& view;
};

class TextUI
{
public:
	//Constructores y destructor
	TextUI(string initialText, ImageCoords_t coords);
	TextUI(string initialText, ImageCoords_t coords, ALLEGRO_FONT* font_);
	TextUI(string initialText, double x_, double y_);
	TextUI(string initialText, double x_, double y_, ALLEGRO_FONT* font_);
	~TextUI();

	//Getters
	string get_text();
	//Setters
	void set_text(string text_);
	void set_coords(ImageCoords_t coords_);
	void set_coords(double x_, double y_);
	//Otros metodos
	void erase_text();

private:
	string text;
	ALLEGRO_FONT* font;
	ImageCoords_t coords;
};