#include "TextUI.h"

#include <cstring>

TextUI::
TextUI(string id, size_t width, size_t height, size_t size, Mode mode) : MouseUI(id, width, height, false, true) {
	this->text = "";
	this->mode = mode;
	this->size = size;
}

TextUI::
~TextUI() {}

void
TextUI::setText(const char* value) {
	string buff = string((char*)value);
	setText(buff);
}

void
TextUI::setText(string value) {
	this->text = "";
	for (unsigned char v : value) {
		this->append(v);
	}
	notifyObservers();
}

void
TextUI::setMode(Mode mode) {
	this->mode = mode;
	notifyObservers();
}

string
TextUI::getText(void) {
	return text;
}

TextUI::Mode
TextUI::getMode(void) {
	return mode;
}

void
TextUI::append(unsigned char value) {
	/* Verifico no llegar al limite */
	if ((strlen(text.c_str()) == size) && size) {
		return;
	}

	/* Hago el cambio de caracter */
	switch (mode) {
		case Mode::NUMBER:
			if (_is_number(value)) {
				this->text += value;
			}
			break;
		case Mode::LETTER:
			if (_is_letter(value)) {
				this->text += value;
			}
			break;
		case Mode::BOTH:
			if (_is_letter(value) || _is_number(value)) {
				this->text += value;
			}
			break;
		case Mode::EVERYTHING:
			this->text += value;
			break;
	}
	notifyObservers();
}

void
TextUI::append(string value) {
	for (unsigned char v : value) {
		this->append(v);
	}
}

void
TextUI::append(const char* value) {
	string values = string(value);
	this->append(values);
}

void
TextUI::remove(void) {
	this->text = this->text.substr(0, text.size() - 1);
	notifyObservers();
}

void
TextUI::clear(void) {
	this->text = "";
	notifyObservers();
}

void
TextUI::setEnterAction(Action enter) {
	this->onEnter = enter;
}

void
TextUI::enter(void* data) {
	if (onEnter)	onEnter(data);
}

bool
TextUI::_is_number(unsigned char value) {
	return (value >= '0' && value <= '9');
}

bool
TextUI::_is_letter(unsigned char value) {
	return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}