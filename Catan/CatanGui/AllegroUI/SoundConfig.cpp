#include "SoundConfig.h"

SoundConfig::
SoundConfig(void) {


}

SoundConfig::
~SoundConfig(void) {}

void
SoundConfig::clear(void) {
	stringConfig.clear();
	intConfig.clear();
}

void
SoundConfig::remove(string index) {
	if (stringConfig.find(index) != stringConfig.end()) {
		_destroy_sample(stringConfig[index].sample);
		stringConfig.erase(index);
	}
}

void
SoundConfig::remove(unsigned int index) {
	if (intConfig.find(index) != intConfig.end()) {
		_destroy_sample(intConfig[index].sample);
		intConfig.erase(index);
	}
}

bool
SoundConfig::setConfig(unsigned int index, const char * filename) {
	config_t myConfig;
	myConfig.sample = _create_sample(filename);
	remove(index);
	intConfig.insert(
		pair<unsigned int, config_t>(
			index,
			myConfig
			)
	);
	return true;
}

bool
SoundConfig::setConfig(string index, const char * filename) {
	config_t myConfig;
	myConfig.sample = _create_sample(filename);
	remove(index);
	stringConfig.insert(
		pair<string, config_t>(
			index,
			myConfig
			)
	);
	return true;
}

ALLEGRO_SAMPLE*
SoundConfig::_create_sample(const char* filename) {
	ALLEGRO_SAMPLE* mySample = al_load_sample(filename);
	return mySample;
}

void
SoundConfig::_destroy_sample(ALLEGRO_SAMPLE* sample) {
	if (sample != nullptr) {
		al_destroy_sample(sample);
	}
}