#include "TextConfig.h"

TextConfig::
TextConfig() {
}

TextConfig::
~TextConfig() {
	_destroy_strings();
	_destroy_ints();
	intConfig.clear();
	stringConfig.clear();
}

void
TextConfig::clear() {
	_destroy_strings();
	_destroy_ints();
	intConfig.clear();
	stringConfig.clear();
}

void
TextConfig::remove(string index) {
	if (stringConfig.find(index) != stringConfig.end()) {
		_destroy_font(index);
		stringConfig.erase(index);
	}
}

void
TextConfig::remove(unsigned int index) {
	if (intConfig.find(index) != intConfig.end()) {
		_destroy_font(index);
		intConfig.erase(index);
	}
}

bool
TextConfig::setConfig(unsigned int index, const char* font, int size) {
	ALLEGRO_FONT* myFont = _create_font(font, size);
	if (myFont != nullptr) {
		remove(index);
		config_t myConfig;
		myConfig.font = myFont;
		intConfig.insert( pair<unsigned int, config_t>(index, myConfig) );
		return true;
	}
	throw exception("TextConfig - No pudo cargar fuente!");
	return false;
}

bool
TextConfig::setConfig(string index, const char* font, int size){
	ALLEGRO_FONT* myFont = _create_font(font, size);
	if (myFont != nullptr) {
		remove(index);
		config_t myConfig;
		myConfig.font = myFont;
		stringConfig.insert(pair<string, config_t>(index, myConfig));
		return true;
	}
	throw exception("TextConfig - No pudo cargar fuente!");
	return false;
}

ALLEGRO_FONT * 
TextConfig::_create_font(const char* file, int size) {
	ALLEGRO_FONT* font = al_load_font(file, size, 0);
	if (font == nullptr) {
		font = al_load_ttf_font(file, size, 0);
	}
	return font;
}

void
TextConfig::_destroy_font(unsigned int index) {
	if (intConfig.find(index) != intConfig.end()) {
		_destroy_font(intConfig[index].font);
	}
}

void
TextConfig::_destroy_font(string index) {
	if (stringConfig.find(index) != stringConfig.end()) {
		_destroy_font(stringConfig[index].font);
	}
}

void
TextConfig::_destroy_font(ALLEGRO_FONT* font) {
	if (font) {
		al_destroy_font(font);
	}
}

void
TextConfig::_destroy_ints() {
	for (auto pair : intConfig) {
		_destroy_font(pair.second.font);
	}
}

void
TextConfig::_destroy_strings() {
	for (auto pair : stringConfig) {
		_destroy_font(pair.second.font);
	}
}
