#include "Coord.h"

extern const string internalDots[22] = {
	"ABE", "BCF", "CFG", "ADE", "BFE",
	"DIH", "DEI", "EIJ", "EFJ", "FJK", "GKL",
	"HIM", "IMN", "JNO", "IJN", "KOJ", "KPL",
	"MNQ", "NOR", "NRQ", "ORS", "OPS"
};

extern const string externalDots[30] = {
	"A05","A0","AB0","B0","BC0","C01",
	"C1", "CG1", "G1", "GL1", "L12", "L2",
	"LP2", "P2", "PS2", "S23", "S3", "RS3",
	"R3", "RQ3", "Q34", "Q4", "QM4", "M4", 
	"MH4", "H45", "H5", "HD5", "D5", "DA5" 
};

extern const string internalEdges[40] = {
	"AB", "BC", "AD", "AE", "BE", "BF", "CF", "CG",
	"DE", "EF", "FG", "DH", "DI", "EI", "EJ", "FJ", "FK", "GK", "GL",
	"HI", "IJ", "JK", "KL", "HM", "IM", "IN", "JN", "JO", "KO", "KP",
	"LP", "MN", "NO", "OP", "MQ", "NQ", "NR", "OR", "OS", "PS"
};

extern const string externalEdges[30] = {
	"A05", "A0B", "B0A", "B0C", "C0", "C10",
	"C1G", "G1C", "G1L", "L1", "L21", "L2P",
	"P2L", "P2S", "S2", "S32", "S3R", "R3S",
	"R3Q", "Q3", "Q43", "Q4M", "M4Q", "M4H",
	"H4", "H54", "H5D", "D5H", "D5A", "A5"
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
		if (coords.size() == 2 || coords.size() == 3) {
			this->type = DOT;
			return;
		}
	}
	else if (c1.isDot() && c2.isDot()) {
		this->coords = c1.coords + c2.coords;
		if (c1.nearCoast() && c2.nearCoast()) {
			if (c1.coords.size() != c2.coords.size()) {
				_handle_repetition_intersection();
			}
		}
		else {
			_handle_repetition_intersection();
		}
		if (coords.size() == 2 || coords.size() == 3) {
			this->type = EDGE;
			return;
		}
	}
	else {
		this->coords = c1.coords + c2.coords;
		_handle_repetition();
		this->type = DOT;
	}
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
	if (coords.size() == coordsCmp.size()) {
		if (isDot()) {
			for (unsigned char coord : coords) {
				if (find(coordsCmp.begin(), coordsCmp.end(), coord) == coordsCmp.end()) {
					return false;
				}
			}
			return true;
		}
		else if (isEdge()) {
			if (_has_numbers()) {
				return coords == coordsCmp;
			}
			else {
				for (unsigned char coord : coords) {
					if (find(coordsCmp.begin(), coordsCmp.end(), coord) == coordsCmp.end()) {
						return false;
					}
				}
				return true;
			}
		}
		else {
			return this->coords == coordsCmp;
		}
	}
	return false;
}

bool
Coord::operator==(Coord copy) {
	return (this->coords == copy.coords) && (this->type == copy.type);
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
	_update_coord();
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
	_verify_type();
	_verify_value();
}

void
Coord::setCoord(string coords, Type type) {
	this->coords = coords;
	this->type = type;
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
	return type == DOT && _is_valid_dot();
}

bool
Coord::isEdge(void) {
	return type == EDGE && _is_valid_edges();
}

bool
Coord::nearCoast(void) {
	return _has_numbers();
}

bool
Coord::nearCoast(Coord coord) {
	if (coord.isSea()) {
		if (_has(coord.coords[0]) ) {
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
	if (coord.isLand()) {
		if (_has(coord.coords[0])) {
			return true;
		}
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
	return false;
}

bool
Coord::isEdgeOf(unsigned char coord) {
	return false;
}

bool
Coord::edgeContinuity(Coord coord) {
	if (isEdge()) {
		if (coord.isEdge()) {
			Coord myCoord(*this, coord);
			return this->isEdgeOf(myCoord) && coord.isEdgeOf(myCoord);
		}
	}
	return false;
}

bool
Coord::edgeContinuity(unsigned char coord) {
	return false;
}

bool
Coord::isAdjacentDot(Coord coord) {
	if (isDot()) {
		if (coord.isDot()) {
			Coord myCoord(*this, coord);
			return myCoord.isEdgeOf(*this) && myCoord.isEdgeOf(coord);
		}
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
			if ( (coords.size() != 3 && coords.size() != 2) || (coords.size() == 2 && _count_numbers() != 1) ) {
				throw exception("Coord - Construccion invalida de un DOT.");
			}
			break;
		case EDGE:
			if ((coords.size() != 3 && coords.size() != 2) || (coords.size() == 2 && _has_numbers()) || (coords.size() == 3 && _count_numbers() != 1)) {
				throw exception("Coord - Construccion invalida de un EDGE.");
			}
			break;
		case LAND:
			if (coords.size() != 1 || (coords.size() == 1 && !_has_letters())) {
				throw exception("Coord - Construccion invalida de un LAND.");
			}
			break;
		case SEA:
			if (coords.size() != 1 || (coords.size() == 1 && !_has_numbers())) {
				throw exception("Coord - Construccion invalida de un LAND.");
			}
			break;
	}
}

void
Coord::_verify_value(void) {
	for (unsigned char c : coords) {
		if ((c < MIN_SEA_COORD || c > MAX_SEA_COORD) && (c < MIN_LAND_COORD || c > MAX_LAND_COORD)) {
			throw exception("Coord - Construccion invalidada por coordenadas incorrectas.");
		}
	}
}

bool
Coord::_is_valid_dot(void) {
	for (string coord : externalDots) {
		if (coord == coords) {
			return true;
		}
	}
	for (string coord : internalDots) {
		if (coord == coords) {
			return true;
		}
	}
	return false;
}

bool
Coord::_is_valid_edges(void) {
	for (string coord : externalEdges) {
		if (coord == coords) {
			return true;
		}
	}
	for (string coord : internalEdges) {
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
	for (string coord : externalDots) {
		if (coord == coords) {
			type = Type::DOT;
			return;
		}
	}
	for (string coord : internalDots) {
		if (coord == coords) {
			type = Type::DOT;
			return;

	for (string coord : internalEdges) {
		if (coord == coords) {
			type = Type::EDGE;
			return;
		}
	}}
	}
	for (string coord : externalEdges) {
		if (coord == coords) {
			type = Type::EDGE;
			return;
		}
	}
	type = Type::NONE;
}