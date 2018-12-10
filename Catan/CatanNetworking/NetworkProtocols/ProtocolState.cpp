#include "ProtocolState.h"

#include <exception>

ProtocolState::
ProtocolState(ProtocolTag* tag, NotifyCallback notify, NetworkSocket** socket, ProtocolType _type) {
	this->tag = tag;
	this->notifyCallback = notify;
	this->hasNotify = true;
	this->socket = socket;
	this->type = _type;
}

ProtocolState::
ProtocolState(ProtocolTag* tag, NotifyCallback callback, ProtocolType _type) {
	this->tag = tag;
	this->notifyCallback = callback;
	this->hasNotify = true;
	this->socket = nullptr;
	this->type = _type;
}

ProtocolState::
ProtocolState(ProtocolTag* tag, ProtocolType _type) {
	this->tag = tag;
	this->hasNotify = false;
	this->socket = nullptr;
	this->type = _type;
}

ProtocolState::ProtocolType
ProtocolState::getType(void) {
	return type;
}

ProtocolState::~ProtocolState(void) {
	if (tag)
		delete tag;
}

ProtocolTag*
ProtocolState::getTag(void) {
	return tag;
}

NotifyCallback
ProtocolState::getNotifyCallback(void) {
	return notifyCallback;
}

map<string, ProtocolState*>* 
ProtocolState::getSubStates(void) {
	return nullptr;
}

void 
ProtocolState::setNotifyCallback(NotifyCallback notify) {
	this->notifyCallback = notify;
	this->hasNotify = true;
}

string 
ProtocolState::getNextTag(void){
	return this->tag->getTag();
}

bool
ProtocolState::shouldNotify(void) const {
	return this->hasNotify;
}

void
ProtocolState::notify(NetworkPacket* packet) {
	if (!hasNotify) {
		throw exception("ProtocolState - notify - Configuracion de protocolo erronea, no deberia notificar!");
	}

	if (this->notifyCallback) {
		this->notifyCallback(packet);
	}
}

void
ProtocolState::setSocket(NetworkSocket** socket) {
	this->socket = socket;
}

bool
ProtocolState::canSend(void) const {
	return socket != nullptr;
}

void 
ProtocolState::sendPacket(NetworkPacket* packet) {
	if (!socket) {
		throw exception("ProtocolState - sendPacket - Configuracion de callback no disponible!");
	}

	(*socket)->send(packet);
}