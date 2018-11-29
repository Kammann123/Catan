#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include <string>

using namespace std;

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


