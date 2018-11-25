#include "PSIfSend.h"

PSIfSend::
PSIfSend(map<string, ProtocolState*> states) : ProtocolState(nullptr) {
	this->states = states;
}

ProtocolStatus
PSIfSend::send(NetworkPacket* packet) {

	/* Verifico si alguno de los subestados tiene razon aqui */
	for (auto statePair : states) {

		ProtocolState* state = statePair.second;
		ProtocolStatus response = state->send(packet);

		/* Si cumple, lo asimilo */
		if (response == ProtocolStatus::DONE) {

			/* Asimilo */
			this->setNotifyCallback(state->getNotifyCallback());
			this->tag = state->getTag();

			return ProtocolStatus::DONE;
		}
	}

	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSIfSend::recv(NetworkPacket* packet) {
	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSIfSend::solve(void) {
	return ProtocolStatus::OK;
}

map<string, ProtocolState*>*
PSIfSend::getSubStates(void) {
	return &states;
}