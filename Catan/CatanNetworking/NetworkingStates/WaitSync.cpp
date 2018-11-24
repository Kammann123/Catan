#include "WaitSync.h"

WaitSync::
WaitSync(CatanNetworking& networking) : NetworkingState(networking) {

}

WaitSync::
~WaitSync() {
	delete protocol;
}

void
WaitSync::run() {

}

void
WaitSync::update() {}

string
WaitSync::what() {
	return string("WAITING_SYNC");
}