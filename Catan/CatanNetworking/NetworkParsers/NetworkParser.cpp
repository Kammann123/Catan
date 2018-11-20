#include "NetworkParser.h"

NetworkParser::
NetworkParser(void) {

	/* Inicializacion */
	this->packets.clear();
	this->status = Status::OK;
	this->error = "";
	this->fsmActive = nullptr;
}

NetworkParser::
~NetworkParser() {

	/* Libero los paquetes de datos */
	for (NetworkPacket* packet : this->packets) {

		delete packet;
	}
}

NetworkParser::Status
NetworkParser::getStatus(void) const {
	return this->status;
}

string
NetworkParser::getError(void) const {
	return this->error;
}

bool
NetworkParser::hasPackets(void) const {
	return !(this->packets.empty());
}

NetworkPacket*
NetworkParser::getNextPacket(void) {

	if (this->packets.empty()) {
		return nullptr;
	}
	else {
		NetworkPacket* packet = this->packets.front();
		this->packets.pop_front();
		return packet;
	}
}

void 
NetworkParser::parse(unsigned char byte) {

	/* Me fijo si alguna fsm esta activa */
	if (this->fsmActive) {

		/* Genero el evento con el byte */
		GenericEvent* event = this->fsmActive->generateEvent(byte);

		/* Ciclo el evento */
		this->fsmActive->cycle(event);
		delete event;

		/* Veo estado de la fsm */
		event = this->fsmActive->getEvent();
		if (event) {

			/* Verifico estado del evento */
			if (event->getType() == ParserStatus::DONE) {
				this->packets.push_back( ((DoneEvent*)event)->getPacket() );
			}
			else if( event->getType() == ParserStatus::ERROR ) {
				this->status = Status::ERROR;
				this->error = ((ErrorEvent*)event)->getError();
			}

			/* Desactivo la fsm */
			this->fsmActive = nullptr;
		}
	}
	else {

		/* Verifico el tipo de dato recibido segun su header */
		switch ((PacketHeader)byte) {
			case PacketHeader::MONOPOLY:
				break;
			case PacketHeader::YEARS_OF_PLENTY:
				break;
			case PacketHeader::KNIGHT:
				break;
			case PacketHeader::BANK_TRADE:
				this->fsmActive = &this->bankParser;
				this->parse(byte);
				break;
			case PacketHeader::CIRCULAR_TOKENS:
				this->fsmActive = &this->tokenParser;
				this->parse(byte);
				break;
			case PacketHeader::CITY: case PacketHeader::SETTLEMENT: case PacketHeader::ROAD:
				this->fsmActive = &this->buildingParser;
				this->parse(byte);
				break;
			case PacketHeader::NAME_IS:
				this->fsmActive = &this->nameParser;
				this->parse(byte);
				break;
			case PacketHeader::MAP_IS:
				this->fsmActive = &this->mapParser;
				this->parse(byte);
				break;
			case PacketHeader::DICES_ARE:
				this->fsmActive = &this->dicesParser;
				this->parse(byte);
				break;
			case PacketHeader::OFFER_TRADE:
				this->fsmActive = &this->offerParser;
				this->parse(byte);
				break;
			case PacketHeader::ROBBER_CARDS:
				this->fsmActive = &this->robberCardParser;
				this->parse(byte);
				break;
			case PacketHeader::ROBBER_MOVE:
				this->fsmActive = &this->robberMoveParser;
				this->parse(byte);
				break;
			case PacketHeader::DEV_CARDS:
				this->fsmActive = &this->devCardParser;
				this->parse(byte);
				break;
			default:
				NetworkPacket* packet = new NetworkPacket((PacketHeader)byte);
				this->packets.push_back(packet);
				break;
		}
	}
}