#include "NetworkingState.h"

NetworkingState::
NetworkingState(CatanNetworking& _networking, unsigned int _id) : networking(_networking), id(_id) {}

NetworkingState::
~NetworkingState() {}

unsigned int
NetworkingState::getId(void) {
	return id;
}