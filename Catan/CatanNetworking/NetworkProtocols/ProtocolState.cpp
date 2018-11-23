#include "ProtocolState.h"

#include <exception>

ProtocolState::
ProtocolState(NotifyCallback callback) {
	this->callback = callback;
	this->hasCallback = true;
}

ProtocolState::
ProtocolState(void) {
	this->hasCallback = false;
}

virtual
ProtocolState::~ProtocolState(void) {}

bool
ProtocolState::shouldNotify(void) const {
	return this->hasCallback;
}

CatanStatus
ProtocolState::notify(NetworkPacket* packet) {
	if (!hasCallback) {
		throw excepction("ProtocolState - notify - Configuracion de protocolo erronea, no deberia notificar!");
	}

	return this->callback(packet);
}