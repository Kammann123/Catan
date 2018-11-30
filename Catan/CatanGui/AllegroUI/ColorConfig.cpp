#include "ColorConfig.h"

ColorConfig::
ColorConfig(void) {
	/* Almaceno los valores por defecto
	*/
	setConfig(DEFAULT_0);
	setConfig(DEFAULT_1);
	setConfig(DEFAULT_2);
	setConfig(DEFAULT_3);
}

ColorConfig::
~ColorConfig(void) {}

void
ColorConfig::clear(void) {
	stringConfig.clear();
	intConfig.clear();
}

void
ColorConfig::remove(string index) {
	if (stringConfig.find(index) != stringConfig.end()) {
		stringConfig.erase(index);
	}
}

void
ColorConfig::remove(unsigned int index) {
	if (intConfig.find(index) != intConfig.end()) {
		intConfig.erase(index);
	}
}

bool
ColorConfig::setConfig(unsigned int index, unsigned char red, unsigned char green, unsigned char blue) {
	config_t myConfig;
	myConfig.color = al_map_rgb(red, green, blue);
	intConfig.insert(
		pair<unsigned int, config_t>(
			index,
			myConfig
		)
	);
	return true;
}

bool
ColorConfig::setConfig(string index, unsigned char red, unsigned char green, unsigned char blue) {
	config_t myConfig;
	myConfig.color = al_map_rgb(red, green, blue);
	stringConfig.insert(
		pair<string, config_t>(
			index,
			myConfig
		)
	);
	return true;
}