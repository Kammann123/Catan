#pragma once
#include "Label.h"

class TextField : public Label
{
public:
	TextField(size_t width, size_t height, pos_t x = 0, pos_t y = 0, Status status = IDLE, string defaultText = "");
	~TextField();

	void addChar(char newChar);
	void removeChar(void);
	void eraseAll(void);

};