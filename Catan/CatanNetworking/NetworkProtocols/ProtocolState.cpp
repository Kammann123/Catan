#include "ProtocolState.h"

#include <exception>

ProtocolState::
ProtocolState(NotifyCallback notify, SendCallback send) {
	this->notifyCallback = notify;
	this->hasNotify = true;
	this->sendCallback = send;
	this->hasSend = true;
}

ProtocolState::
ProtocolState(NotifyCallback callback) {
	this->notifyCallback = callback;
	this->hasNotify = true;
	this->hasSend = false;
}

ProtocolState::
ProtocolState(SendCallback callback) {
	this->sendCallback = callback;
	this->hasNotify = false;
	this->hasSend = true;
}

ProtocolState::
ProtocolState(void) {
	this->hasNotify = false;
	this->hasSend = false;
}

ProtocolState::~ProtocolState(void) {}

bool
ProtocolState::shouldNotify(void) const {
	return this->hasNotify;
}

CatanStatus
ProtocolState::notify(NetworkPacket* packet) {
	if (!hasNotify) {
		throw exception("ProtocolState - notify - Configuracion de protocolo erronea, no deberia notificar!");
	}

	return this->notifyCallback(packet);
}

void
ProtocolState::setSendCallback(SendCallback send) {
	this->sendCallback = send;
	this->hasSend = true;
}

bool
ProtocolState::canSend(void) const {
	return this->hasSend;
}

void 
ProtocolState::sendPacket(NetworkPacket* packet) {
	if (!hasSend) {
		throw exception("ProtocolState - sendPacket - Configuracion de callback no disponible!");
	}

	this->sendCallback(packet);
}