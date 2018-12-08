#include "Destroyer.h"

/************
* Destroyer *
************/

Destroyer::
Destroyer(void* connector) {
	this->connector = connector;
}

Destroyer::
~Destroyer(void) {
	delete this->connector;
}