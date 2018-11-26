#include "TokenData.h"

TokenData::
TokenData(map<Coord, unsigned char> tokens) : CatanData(CatanData::Type::TOKEN) {
	this->tokens = tokens;
}

TokenData::
TokenData(void) : CatanData(CatanData::Type::TOKEN) {}

bool
TokenData::setToken(Coord coord, unsigned char token) {
	if (isValidToken(token)) {
		this->tokens[coord] = token;
		return true;
	}

	return false;
}

unsigned char
TokenData::getToken(unsigned char coord) {
	if (tokens.find(coord) != tokens.end()) {
		return tokens[coord];
	}

	return -1;
}

map<Coord, unsigned char>&
TokenData::getTokens() {
	return tokens;
}