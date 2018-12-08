#include "ImageConfig.h"

ImageConfig::
ImageConfig() {}

ImageConfig::
~ImageConfig() {
	this->clear();
}

void
ImageConfig::clear(void) {
	for (auto value : intConfig) {
		if (value.second.bitmap ) {
			al_destroy_bitmap(value.second.bitmap);
		}
	}
	for (auto value : stringConfig) {
		if (value.second.bitmap) {
			al_destroy_bitmap(value.second.bitmap);
		}
	}
	intConfig.clear();
	stringConfig.clear();
}

void
ImageConfig::remove(string index) {
	if (stringConfig.find(index) != stringConfig.end()) {
		_destroy_bitmap(stringConfig[index].bitmap);
		stringConfig.erase(index);
	}
}

void
ImageConfig::remove(unsigned int index) {
	if (intConfig.find(index) != intConfig.end() ){
		_destroy_bitmap(intConfig[index].bitmap);
		intConfig.erase(index);
	}
}

bool
ImageConfig::setConfig(unsigned int index, const char* image) {
	ALLEGRO_BITMAP* bitmap = _create_bitmap(image);
	if (bitmap != nullptr) {
		if (intConfig.find(index) != intConfig.end()) {
			remove(index);
		}
		config_t myBitmap;
		myBitmap.bitmap = bitmap;
		intConfig.insert(pair<unsigned int, config_t>(index, myBitmap));
		return true;
	}
	throw exception("ImageConfig - No pudo cargar imagen!");
	return false;
}

bool
ImageConfig::setConfig(string index, const char* image) {
	ALLEGRO_BITMAP* bitmap = _create_bitmap(image);
	if (bitmap != nullptr) {
		if (stringConfig.find(index) != stringConfig.end()) {
			remove(index);
		}
		config_t myBitmap;
		myBitmap.bitmap = bitmap;
		stringConfig.insert(pair<string, config_t>(index, myBitmap));
		return true;
	}
	throw exception("ImageConfig - No pudo cargar imagen!");
	return false;
}

ALLEGRO_BITMAP*
ImageConfig::_create_bitmap(const char* image) {
	ALLEGRO_BITMAP* myBitmap = al_load_bitmap(image);
	return myBitmap;
}

void
ImageConfig::_destroy_bitmap(ALLEGRO_BITMAP* bitmap) {
	if (bitmap != nullptr) {
		al_destroy_bitmap(bitmap);
	}
}