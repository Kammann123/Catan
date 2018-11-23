#include "Protocol.h"

Protocol::
Protocol(SendCallback sendCallback, vector<ProtocolState*> states) {
	/* Inicializo */
	this->states = states;
	this->currentState = 0;
	this->status = ProtocolStatus::OK;
	this->error = "";

	/* Configuro el callback */
	for (ProtocolState* p : states) {
		p->setSendCallback(sendCallback);
	}

	/* Ejecuto solve del primer estado */
	transition(this->states[this->currentState]->solve());
}

ProtocolStatus
Protocol::getStatus(void) const {
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
	this->currentState = 0;
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
		if (states[currentState]->shouldNotify()) {
			states[currentState]->notify(packet);
		}

		/* Muevo el protocolo de estado */
		currentState++;
		if (currentState >= states.size()) {
			this->status = status;
			this->error = "";
		}
		else {
			transition(this->states[currentState]->solve());
		}
		break;

		/* El estado de protocolo responde correctamente, sin indicar
		* un cambio resuelto aun, y se mantiene esperando! */
	case ProtocolStatus::OK:
		break;

		/* El estado de protocolo responde un error, indicando que
		* no recibio correctamente lo que esperaba! */
	case ProtocolStatus::ERROR:
		this->status = status;
		this->error = "Hubo un error en el protocolo de comunicacion!";
		break;
	}
}

void
Protocol::transition(ProtocolStatus status) {
	switch (status) {

		/* El estado de protocolo recibio lo que esperaba, con lo que
		* ejecuta su proposito y termina. Se cambia a siguiente estado
		* y se ejecuta rutina solve, si se acaban estados, el protocolo
		* tambien termino! */
	case ProtocolStatus::DONE:

		/* Muevo el protocolo de estado */
		currentState++;
		if (currentState >= states.size()) {
			this->status = status;
			this->error = "";
		}
		else {
			transition(this->states[currentState]->solve());
		}
		break;

		/* El estado de protocolo responde correctamente, sin indicar
		* un cambio resuelto aun, y se mantiene esperando! */
	case ProtocolStatus::OK:
		break;

		/* El estado de protocolo responde un error, indicando que
		* no recibio correctamente lo que esperaba! */
	case ProtocolStatus::ERROR:
		this->status = status;
		this->error = "Hubo un error en el protocolo de comunicacion!";
		break;
	}
}

void 
Protocol::send(NetworkPacket* packet) {
	verifyStatus();

	ProtocolStatus response = this->states[currentState]->send(packet);

	transition(response, packet);
}

void
Protocol::recv(NetworkPacket* packet) {
	verifyStatus();

	ProtocolStatus response = this->states[currentState]->recv(packet);

	transition(response, packet);
}

void
Protocol::verifyStatus(void) const {
	if (status == ProtocolStatus::DONE) {
		throw exception("Protocol - verifyStatus - El protocolo termino, revisar getStatus!");
	}
	else if (status == ProtocolStatus::ERROR ){
		throw exception("Protocol - verifyStatus - El protocolo tuvo un error, revisar getStatus!");
	}
}