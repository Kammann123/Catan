#include "Coord.h"

extern const string edges[72] = {
	"0A5", "0AB", "0BA", "0BC", "0C", "1C0",
	"5A", "AB", "BC", "1CG",
	"5DA", "AD", "AE", "BE", "BF", "CF", "CG", "1GC",
	"5DH", "DE", "EF", "FG", "1GL",
	"5HD", "DH", "DI", "EI", "EJ", "FJ", "FK", "GK", "GL", "1L",
	"5H4", "HI", "IJ", "JK", "KL", "2L1",
	"H4", "HM", "IM", "IN", "JN", "JO", "KO", "KP", "LP", "2LP",
	"4MH", "MN", "NO", "OP", "2PL",
	"4MQ", "MQ", "NQ", "NR", "OR", "OS", "PS", "2PS",
	"4QM", "QR", "RS", "2S",
	"4Q3", "3Q", "3RQ", "3RS", "3SR", "3S2"
};

extern const string externalDots[30] = {
	"05A", "0A", "0AB", "0B", "0BC", "01C", "1C",
	"1CG", "1G", "1GL", "12L", "2L", "2LP",
	"2P", "2PS", "23S", "3S", "3SR", "3R",
	"3RQ", "34Q", "4Q", "4MQ", "4M", "4HM",
	"45H", "5H", "5DH", "5D", "5AD"
};

extern const string internalDots[24] = {
	"ABE", "BCF", "ADE", "BEF", "CFG",
	"DEI", "EFJ", "FGK", "DHI", "EIJ",
	"FJK", "GKL", "HIM", "IJN", "JKO",
	"KLP", "IMN", "JNO", "KOP", "NMQ",
	"NOR", "OPS", "NQR", "ORS"
};

Coord::
Coord(void) {
	this->coords = "";
	this->type = Type::NONE;
}

Coord::
Coord(string coords) {
	this->coords = coords;
	_update_coord();
}

Coord::
Coord(string coords, Type type) {
	this->coords = coords;
	this->type = type;
	
	_verify_value();
	_verify_type();
}

Coord::
Coord(const Coord& copy) {
	this->coords = copy.coords;
	this->type = copy.type;
}

Coord::
Coord(unsigned char coord) {
	this->coords = coord;
	if (_has_numbers()) {
		this->type = Type::SEA;
	}
	else {
		this->type = Type::LAND;
	}
	_verify_value();
	_verify_type();
}

Coord::
Coord(Coord c1, Coord c2) {
	if (c1.isEdge() && c2.isEdge()) {
		this->coords = c1.coords + c2.coords;
		if (c1.nearCoast() && c2.nearCoast()) {
			_handle_repetition_intersection();
		}
		else {
			_handle_repetition();
		}
		type = Type::DOT;
		_order_refactor();
		return;
	}
	else if (c1.isDot() && c2.isDot()) {
		this->coords = c1.coords + c2.coords;
		if (c1.nearCoast() && c2.nearCoast()) {
			if (c1.coords.size() != c2.coords.size()) {
				_handle_repetition();
			}
		}
		else {
			_handle_repetition_intersection();
		}
		type = Type::EDGE;
		_order_refactor();
		return;
	}

	this->type = NONE;
}

Coord::
Coord(vector<unsigned char> coord) {
	for (unsigned char c : coord) {
		this->coords += c;
	}
	_handle_repetition();
	_verify_value();
	_verify_type();
}

bool
Coord::operator<(const Coord& coord) const {
	return this->coords < coord.coords;
}

bool
Coord::operator<=(const Coord& coord) const {
	return this->coords <= coord.coords;
}

bool
Coord::operator>(const Coord& coord)  const {
	return this->coords > coord.coords;
}

bool
Coord::operator>=(const Coord& coord)  const {
	return this->coords >= coord.coords;
}

bool
Coord::operator==(string coordsCmp) {
	return coordsCmp == coords;
}

bool
Coord::operator==(Coord copy) {
	return this->coords == copy.coords && this->type == copy.type;
}

bool
Coord::operator==(unsigned char coord) {
	if (isLand() || isSea()) {
		return this->coords[0] == coord;
	}
	return false;
}

unsigned char
Coord::operator[](unsigned int index) {
	return coords[index];
}

Coord&
Coord::operator=(unsigned char coord) {
	this->coords = coord;
	_update_coord();
	return *this;
}

Coord&
Coord::operator=(string coords) {
	this->coords = coords;
	_update_coord();
	return *this;
}

Coord&
Coord::operator=(Coord coords) {
	this->coords = coords.coords;
	this->type = coords.type;
	return *this;
}

Coord&
Coord::operator+=(unsigned char coord) {
	this->coords += coord;
	_update_coord();
	return *this;
}

Coord&
Coord::operator+=(string coords) {
	this->coords += coords;
	_update_coord();
	return *this;
}

Coord&
Coord::operator+=(Coord coords) {
	this->coords += coords.coords;
	_update_coord();
	return *this;
}

void
Coord::setCoord(unsigned char coord) {
	this->coords = coord;
	if (_has_numbers()) {
		this->type = Type::SEA;
	}
	else {
		this->type = Type::LAND;
	}
	_update_coord();
	_verify_type();
	_verify_value();
}

void
Coord::setCoord(string coords, Type type) {
	this->coords = coords;
	this->type = type;
	_update_coord();
	_verify_type();
	_verify_value();
}

void
Coord::forceEdge(void) {
	type = Type::EDGE;
}

void
Coord::forceDot(void) {
	type = Type::DOT;
}

string
Coord::getCoords(void)  {
	return coords;
}

list<Coord> 
Coord::getLandCoords(void) {
	list<Coord> landCoords;
	for (unsigned char c : coords) {
		Coord myCoord = Coord(c);
		if (myCoord.isLand()) {
			landCoords.push_back(myCoord);
		}
	}
	return landCoords;
}

list<Coord> 
Coord::getSeaCoords(void) {
	list<Coord> landCoords;
	for (unsigned char c : coords) {
		Coord myCoord = Coord(c);
		if (myCoord.isSea()) {
			landCoords.push_back(myCoord);
		}
	}
	return landCoords;
}

string::iterator 
Coord::begin(void) {
return coords.begin();
}

string::iterator
Coord::end(void) {
	return coords.end();
}

size_t
Coord::size(void) {
	return coords.size();
}

bool
Coord::isSea(void) {
	return type == SEA;
}

bool
Coord::isLand(void) {
	return type == LAND;
}

bool
Coord::isDot(void) {
	return type == DOT;
}

bool
Coord::isEdge(void) {
	return type == EDGE;
}

bool
Coord::nearCoast(void) {
	return _has_numbers();
}

bool
Coord::nearCoast(Coord coord) {
	if (coord.isSea()) {
		if (_has(coord.coords[0])) {
			return true;
		}
	}
	return false;
}

bool
Coord::nearCoast(unsigned char coord) {
	Coord myCoord(coord);
	return nearCoast(myCoord);
}

bool
Coord::isVertexOf(Coord coord) {
	if (!coord.isLand() && !this->isLand()) {
		return false;
	}

	if (coord.isLand()) {
		if (isDot()) {
			if (_has(coord.coords[0])) {
				return true;
			}
		}
	}
	else if (coord.isVertexOf(*this)) {
		return true;
	}

	return false;
}

bool
Coord::isVertexOf(unsigned char coord) {
	if (isDot()) {
		if (_has(coord)) {
			return true;
		}
	}
	return false;
}

bool
Coord::isEdgeOf(Coord coord) {
	if (!coord.isEdge() && !this->isEdge()) {
		return false;
	}

	if (isEdge()) {
		if (coord.isDot()) {
			if (coord.coords.size() == 3) {
				for (unsigned char c : coords) {
					if (find(coord.coords.begin(), coord.coords.end(), c) == coord.coords.end()) {
						return false;
					}
				}
				return true;
			}
			else if (coord.coords.size() == 2) {
				for (unsigned char c : coord.coords) {
					if (find(coords.begin(), coords.end(), c) == coords.end()) {
						return false;
					}
				}
				return true;
			}
		}
	}
	else if (coord.isEdgeOf(*this)){
		return true;
	}

	return false;
}

bool
Coord::isEdgeOf(unsigned char coord) {
	return false;
}

bool
Coord::edgeContinuity(Coord coord) {
	if (!coord.isEdge() && !this->isEdge()) {
		return false;
	}

	if (isEdge()) {
		if (coord.isEdge()) {
			Coord myCoord(*this, coord);
			return this->isEdgeOf(myCoord) && coord.isEdgeOf(myCoord);
		}
	}
	else if (coord.edgeContinuity(*this)) {
		return true;
	}

	return false;
}

bool
Coord::edgeContinuity(unsigned char coord) {
	return false;
}

bool
Coord::isAdjacentDot(Coord coord) {
	if (!coord.isDot() && !this->isDot()) {
		return false;
	}

	if (isDot()) {
		if (coord.isDot()) {
			Coord myCoord(*this, coord);
			return myCoord.isEdgeOf(*this) && myCoord.isEdgeOf(coord);
		}
	}
	else if (coord.isAdjacentDot(*this)) {
		return true;
	}

	return false;
}

bool
Coord::isAdjacentDot(unsigned char coord) {
	return false;
}

bool
Coord::_has_numbers(void) {
	for (unsigned char c : coords) {
		if (c >= MIN_SEA_COORD && c <= MAX_SEA_COORD) {
			return true;
		}
	}
	return false;
}

bool
Coord::_has_letters(void) {
	for (unsigned char c : coords) {
		if (c >= MIN_LAND_COORD && c <= MAX_LAND_COORD) {
			return true;
		}
	}
	return false;
}

unsigned int
Coord::_count_numbers(void) {
	unsigned int count = 0;
	for (unsigned char c : coords) {
		if (c >= '0' && c <= '9') {
			count++;
		}
	}
	return count;
}

bool
Coord::_has(unsigned char coord) {
	for (unsigned char c : coords) {
		if (coord == c) {
			return true;
		}
	}
	return false;
}

void
Coord::_handle_repetition(void) {
	map<unsigned char, unsigned char> coordCount;

	for (unsigned char i = '0'; i <= '5'; i++) coordCount.insert(pair<unsigned char, unsigned char>(i, 0));
	for (unsigned char i = 'A'; i <= 'S'; i++) coordCount.insert(pair<unsigned char, unsigned char>(i, 0));

	string newCoords;
	for (unsigned char c : coords) {

		if (!coordCount[c]) {
			coordCount[c]++;
			newCoords += c;
		}
	}
	
	coords = newCoords;
}

void
Coord::_handle_repetition_intersection(void) {
	map<unsigned char, unsigned char> coordCount;

	for (unsigned char i = '0'; i <= '5'; i++) coordCount.insert(pair<unsigned char, unsigned char>(i, 0));
	for (unsigned char i = 'A'; i <= 'S'; i++) coordCount.insert(pair<unsigned char, unsigned char>(i, 0));

	string newCoords;
	for (unsigned char c : coords) {

		if (coordCount[c] < 1) {
			coordCount[c]++;
		}
		else if(coordCount[c] == 1) {
			newCoords += c;
		}
	}

	coords = newCoords;
}

void
Coord::_verify_type(void) {

	switch (type) {
		case DOT:
			for (string coord : internalDots) {
				if (coord == coords) {
					return;
				}
			}
			for (string coord : externalDots) {
				if (coord == coords) {
					return;
				}
			}
			break;
		case EDGE:
			for (string coord : edges) {
				if (coord == coords) {
					return;
				}
			}
			break;
		case LAND:
			if (coords.size() == 1 && !_has_numbers()) {
				return;
			}
			break;
		case SEA:
			if (coords.size() == 1 && _has_numbers()) {
				return;
			}
			break;
	}
	type = Type::NONE;
}

void
Coord::_verify_value(void) {
	for (unsigned char c : coords) {
		if ((c < MIN_SEA_COORD || c > MAX_SEA_COORD) && (c < MIN_LAND_COORD || c > MAX_LAND_COORD)) {
			type = Type::NONE;
		}
	}
}

bool
Coord::_is_valid_dot(void) {
	for (string coord : internalDots) {
		if (coord == coords) {
			return true;
		}
	}
	for (string coord : externalDots) {
		if (coord == coords) {
			return true;
		}
	}
	return false;
}

bool
Coord::_is_valid_edges(void) {
	for (string coord : edges) {
		if (coord == coords) {
			return true;
		}
	}
	return false;
}

bool
Coord::_is_valid_land(void) {
	if (coords.size() == 1) {
		return ((coords[0] >= MIN_LAND_COORD) && (coords[0] <= MAX_LAND_COORD));
	}
	return false;
}

bool
Coord::_is_valid_sea(void) {
	if (coords.size() == 1) {
		return ((coords[0] >= MIN_SEA_COORD) && (coords[0] <= MAX_SEA_COORD));
	}
	return false;
}

void
Coord::_update_coord(void) {
	if (coords.size() == 1){
		if (_is_valid_sea()) {
			type = Type::SEA;
			return;
		}
		else if (_is_valid_land()) {
			type = Type::LAND;
			return;
		}
	}
	for (string coord : internalDots) {
		if (coord == coords) {
			type = Type::DOT;
			return;
		}
	}
	for (string coord : externalDots) {
		if (coord == coords) {
			type = Type::DOT;
			return;
		}
	}
	for (string coord : edges) {
		if (coord == coords) {
			type = Type::EDGE;
			return;
		}
	}
	type = Type::NONE;
}

void
Coord::_order_refactor(void) {
	bool ok = true;

	if (isEdge()) {
		ok = true;
		for (string coord : edges) {
			if (coords.size() == coord.size()) {
				for (unsigned char c : coord) {
					if (find(coords.begin(), coords.end(), c) == coords.end()) {
						ok = false;
						break;
					}
				}
				if (ok) {
					coords = coord;
					return;
				}
				ok = true;
			}
		}
	}
	else if (isDot()) {
		ok = true;
		for (string coord : externalDots) {
			if (coords.size() == coord.size()) {
				for (unsigned char c : coord) {
					if (find(coords.begin(), coords.end(), c) == coords.end()) {
						ok = false;
						break;
					}
				}
				if (ok) {
					coords = coord;
					return;
				}
				ok = true;
			}
		}
		ok = true;
		for (string coord : internalDots) {
			if (coords.size() == coord.size()) {
				for (unsigned char c : coord) {
					if (find(coords.begin(), coords.end(), c) == coords.end()) {
						ok = false;
						break;
					}
				}
				if (ok) {
					coords = coord;
					return;
				}
				ok = true;
			}
		}
	}

	type = Type::NONE;
}