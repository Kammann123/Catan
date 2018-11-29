#include "TextField.h"
#include "../AllegroUI/FrameUI.h"


TextField::TextField(size_t width, size_t height, pos_t x, pos_t y, Status status, string defaultText) : Label(width, height, x, y, status, defaultText){}

TextField::~TextField(){}

void 
TextField::addChar(char newChar) {
	Label::setText(Label::getText() + newChar);
}

void
TextField::removeChar(){
	string text = Label::getText();
	if (text.size() >0)										//Si hay algun caracter
		Label::set_text(text.substr(0, text.size() - 1));	//Se elimina el ultimo caracter
}

void 
TextField::eraseAll(void) {
	Label::setText("");
}