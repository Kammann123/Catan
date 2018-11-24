#include "PSIfRecv.h"
#include "PSRecv.h"

PSIfRecv::
PSIfRecv(map<string, ProtocolState*> states) : ProtocolState(nullptr) {
	this->states = states;
}

ProtocolStatus
PSIfRecv::send(NetworkPacket* packet) {
	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSIfRecv::recv(NetworkPacket* packet) {

	/* Reviso para todos los subestados */
	for (auto statePair : states) {

		ProtocolState* state = statePair.second;
		ProtocolStatus response = state->recv(packet);

		/* Si le pega a alguno, asimilo su respuesta */
		if (response == ProtocolStatus::DONE) {

			this->setNotifyCallback(state->getNotifyCallback());
			this->tag = state->getTag();

			return ProtocolStatus::DONE;
		}
	}

	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSIfRecv::solve() {}

map<string, ProtocolState*>* 
PSIfRecv::getSubStates(void) {
	return &states;
}