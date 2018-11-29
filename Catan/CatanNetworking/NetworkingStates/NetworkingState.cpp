#include "NetworkingState.h"

NetworkingState::
NetworkingState(CatanNetworking& _networking, unsigned int timeout, unsigned int _id) : networking(_networking), id(_id) {
	this->hasTimeout = true;
	this->timeout = boost::chrono::seconds(timeout);
}

NetworkingState::
NetworkingState(CatanNetworking& _networking, unsigned int _id) : networking(_networking), id(_id) {
	this->hasTimeout = false;
}

NetworkingState::
~NetworkingState() {}

unsigned int
NetworkingState::getId(void) {
	return id;
}

void
NetworkingState::resetTime(void) {
	if (this->hasTimeout) {
		this->startTime = boost::chrono::steady_clock::now();
	}
}

bool
NetworkingState::timeoutStatus(void) {
	
	/* Verifico que este configurado el timeout */
	if (this->hasTimeout) {
		if ((boost::chrono::steady_clock::now() - startTime) > timeout) {
			return false;
		}
	}

	/* 
	* O bien no tiene configurada dicha caracteristica, o bien sucede que 
	* no hubo un error del tipo timeout, devuelve OK
	*/
	return true;
}