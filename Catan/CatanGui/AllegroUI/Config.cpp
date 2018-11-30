#include "Config.h"

Config::
Config() {}

Config::
~Config() {}

config_t
Config::operator[](string index) {
	if (stringConfig.find(index) == stringConfig.end()) {
		throw exception("Config - No se pudo encontrar el indice [] con Config.");
	}
	else {
		return stringConfig[index];
	}
}

config_t
Config::operator[](unsigned int index) {
	if (intConfig.find(index) == intConfig.end()) {
		throw exception("Config - No se pudo encontrar el indice [] con Config.");
	}
	else {
		return intConfig[index];
	}
}

bool
Config::has(void) {
	return intConfig.size() || stringConfig.size();
}

bool
Config::has(unsigned int index) {
	return intConfig.find(index) != intConfig.end();
}

bool
Config::has(string index) {
	return stringConfig.find(index) != stringConfig.end();
}