#include "Protocol.h"

#include <list>

Protocol::
Protocol(NetworkSocket** socket, string start, unsigned int timeout, map<string, ProtocolState*> states) {
	/* Inicializo */
	this->states = states;
	this->currState = start;
	this->startState = start;
	this->status = ProtocolStatus::OK;
	this->error = "";
	this->timeout = boost::chrono::milliseconds(timeout);
	this->hasTimeout = true;

	_init_callback(socket);
	_init_substates();
}

Protocol::
Protocol(NetworkSocket** socket, string start, map<string, ProtocolState*> states) {
	/* Inicializo */
	this->states = states;
	this->currState = start;
	this->startState = start;
	this->status = ProtocolStatus::OK;
	this->error = "";
	this->hasTimeout = false;

	_init_callback(socket);
	_init_substates();
}

Protocol::
~Protocol() {
	/* Configuro el callback */
	for (auto ps : this->states) {
		delete ps.second;
	}
}

void
Protocol::_init_callback(NetworkSocket** socket) {

	/* Configuro el callback */
	for (auto ps : this->states) {
		ps.second->setSocket(socket);
	}
}

void
Protocol::_init_substates() {


	/* Cargo todos los subestados para permitir interconexion! */
	list<map<string, ProtocolState*>*> subMaps;

	/* Busco los sub mapas de todos */
	for (auto ps : this->states) {

		if (ps.second->getSubStates()) {

			subMaps.push_back(ps.second->getSubStates());
		}
	}

	/* Los cargo todos */
	for (auto map : subMaps) {

		for (auto state : *map) {

			this->states[state.first] = state.second;
		}
	}
}

void
Protocol::resetTime(void) {
	if (hasTimeout) {
		startTime = boost::chrono::steady_clock::now();
	}
}

ProtocolStatus
Protocol::getStatus(void) {

	/* Verifico timeout */
	if (status == ProtocolStatus::OK && hasTimeout ) {

		if ((boost::chrono::steady_clock::now() - startTime) > timeout) {

			this->status = ProtocolStatus::TIMEOUT;
		}
	}

	/* Devuelvo estado */
	return this->status;
}

string
Protocol::getError(void) const {
	return this->error;
}

void 
Protocol::reset(void) {
	this->status = ProtocolStatus::OK;
	this->error = "";
	this->currState = this->startState;
}

void
Protocol::start(void) {

	if (this->currState == this->startState) {

		/* Ejecuto solve del primer estado */
		transition(this->states[this->currState]->solve());

		/* Reinicio timeout */
		resetTime();
	}
}

void
Protocol::transition(ProtocolStatus status, NetworkPacket* packet) {
	switch (status) {

		/* El estado de protocolo recibio lo que esperaba, con lo que
		* ejecuta su proposito y termina. Se cambia a siguiente estado
		* y se ejecuta rutina solve, si se acaban estados, el protocolo
		* tambien termino! */
	case ProtocolStatus::DONE:

		/* Verifico si debo notificarlo */
		if (packet) {
			if (states[currState]->shouldNotify()) {
				states[currState]->notify(packet);
			}
		}

		/* Muevo el protocolo de estado */
		this->currState = this->states[currState]->getNextTag();
		if ( this->currState == PROTOCOL_DONE ) {
			this->status = status;
			this->error = "";
		}
		else {

			if (hasTimeout) {
				resetTime();
			}

			transition(this->states[currState]->solve());
		}
		break;

		/* El estado de protocolo responde correctamente, sin indicar
		* un cambio resuelto aun, y se mantiene esperando! */
	case ProtocolStatus::OK:
		break;

		/* El estado de protocolo responde un error, indicando que
		* no recibio correctamente lo que esperaba! */
	case ProtocolStatus::PROTOCOL_ERROR:
		this->status = status;
		this->error = "Hubo un error en el protocolo de comunicacion!";
		break;
	}
}

void 
Protocol::send(NetworkPacket* packet) {
	verifyStatus();

	ProtocolStatus response = this->states[currState]->send(packet);

	transition(response, packet);
}

void
Protocol::recv(NetworkPacket* packet) {
	verifyStatus();

	ProtocolStatus response = this->states[currState]->recv(packet);

	transition(response, packet);
}

void
Protocol::verifyStatus(void) const {
	if (status == ProtocolStatus::DONE) {
		throw exception("Protocol - verifyStatus - El protocolo termino, revisar getStatus!");
	}
	else if (status == ProtocolStatus::PROTOCOL_ERROR){
		throw exception("Protocol - verifyStatus - El protocolo tuvo un error, revisar getStatus!");
	}
}