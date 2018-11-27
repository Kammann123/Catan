#pragma once
#include<allegro5/allegro.h>
#include <string>

using namespace std;

typedef struct 
{
	double x;
	double y;
}ImageCoords_t;

using callback = ;
using pixel = unsigned int;

class SelectionFeature {
public:
	/* Constructor / Destructor */
	SelectionFeature();
	~SelectionFeature();

	void toggleSelection(void);
	bool isSelected(void);
	bool isFocused(void);

private:

	bool selected;
	bool focused;
};


class TextField {
public:
	/* Constructor / Destructor */
	TextField(pixel width, pixel size);
	~TextField();

	void addChar(unsigned char newChar);
	void deleteChar(void);
	void eraseAll(void);
	void toggleSelection(void);

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
	ImageCoords_t coords;
	//ALLEGRO_FONT* font; <- no se si el tipo de dato es ese

};

class ImageWidget{
public:
	/* Constructor / Destructor */
	ImageWidget(ALLEGRO_DISPLAY* display_, ALLEGRO_BITMAP* bitmap_);
	~ImageWidget();

	 /* Getters */
	ALLEGRO_BITMAP* getBitmap(void);
	ALLEGRO_DISPLAY* getDisplay(void);
	ImageCoords_t getCoords(void);


	/* Setters */
	void setBitmap(ALLEGRO_BITMAP* newBitmap);
	void setDisplay(ALLEGRO_DISPLAY* newDisplay);
	void setCoords(ImageCoords_t newCoords);



private:
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_DISPLAY* display;
	ImageCoords_t coords;
};