#include "ProtocolState.h"

#include <exception>

ProtocolState::
ProtocolState(ProtocolTag* tag, NotifyCallback notify, NetworkSocket** socket) {
	this->tag = tag;
	this->notifyCallback = notify;
	this->hasNotify = true;
	this->socket = socket;
}

ProtocolState::
ProtocolState(ProtocolTag* tag, NotifyCallback callback) {
	this->tag = tag;
	this->notifyCallback = callback;
	this->hasNotify = true;
	this->socket = nullptr;
}

ProtocolState::
ProtocolState(ProtocolTag* tag) {
	this->tag = tag;
	this->hasNotify = false;
	this->socket = nullptr;
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

	return this->notifyCallback(packet);
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