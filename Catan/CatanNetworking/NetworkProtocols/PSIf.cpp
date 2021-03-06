#include "PSIf.h"

PSIf::
PSIf(map<string, ProtocolState*> states) : ProtocolState(nullptr, ProtocolState::BOTH) {
	this->states = states;
	this->hasNotify = false;
}

ProtocolStatus
PSIf::send(NetworkPacket* packet) {

	/* Verifico si alguno de los subestados tiene razon aqui */
	for (auto statePair : states) {

		ProtocolState* state = statePair.second;

		/* Verifico que sea teller o both */
		if (state->getType() == TELLER || state->getType() == BOTH) {
			ProtocolStatus response = state->send(packet);

			/* Si cumple, lo asimilo */
			if (response == ProtocolStatus::DONE) {

				/* Asimilo */
				if (state->shouldNotify()) {
					this->setNotifyCallback(state->getNotifyCallback());
				}
				else {
					this->hasNotify = false;
				}
				this->tag = state->getTag();

				return ProtocolStatus::DONE;
			}
		}
	}

	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSIf::recv(NetworkPacket* packet) {

	/* Reviso para todos los subestados */
	for (auto statePair : states) {

		ProtocolState* state = statePair.second;

		/* Verifico que sea listener o both */
		if (state->getType() == LISTENER || state->getType() == BOTH) {
			ProtocolStatus response = state->recv(packet);

			/* Si le pega a alguno, asimilo su respuesta */
			if (response == ProtocolStatus::DONE) {
				/* Asimilo */
				if (state->shouldNotify()) {
					this->setNotifyCallback(state->getNotifyCallback());
				}
				else {
					this->hasNotify = false;
				}
				this->tag = state->getTag();

				return ProtocolStatus::DONE;
			}
		}
	}

	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSIf::solve(void) {
	return ProtocolStatus::OK;
}

map<string, ProtocolState*>*
PSIf::getSubStates(void) {
	return &states;
}

bool
PSIf::isHeader(PacketHeader header) {
	for (auto state : states) {
		if (state.second->isHeader(header)) {
			return true;
		}
	}
	return false;
}

bool
PSIf::isHeader(PacketHeader header, ProtocolState::ProtocolType asWhat) {
	for (auto state : states) {
		if (state.second->isHeader(header) && asWhat == state.second->getType()) {
			return true;
		}
	}
	return false;
}

void 
PSIf::setSocket(NetworkSocket** socket) {
	this->socket = socket;

	for (auto state : states) {

		if (state.second) {
			state.second->setSocket(socket);
		}
	}
}