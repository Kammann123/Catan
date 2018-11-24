#include "WaitSync.h"

#include "../CatanNetworking.h"

#include "NetError.h"
#include "Idle.h"

WaitSync::
WaitSync(CatanNetworking& networking) : NetworkingState(networking) {


	/* Definimos el protocolo de sincronizacion de cliente */
	this->syncProtocol = protocol(
		socket_send(networking.getSocket()),
		"LOCAL_REQUEST",
		p_recv("LOCAL_REQUEST", tag("LOCAL_SEND"), PacketHeader::NAME),
		p_data_send("LOCAL_SEND", tag("LOCAL_ACK"), bind(&WaitSync::getLocalName, this)),
		p_recv("LOCAL_ACK", tag("REMOTE_REQUEST"), PacketHeader::ACK),
		p_send("REMOTE_REQUEST", tag("REMOTE_RECV"), PacketHeader::NAME),
		p_recv("REMOTE_RECV", tag("REMOTE_ACK"), bind(&WaitSync::setRemoteName, this, _1), PacketHeader::NAME_IS),
		p_send("REMOTE_ACK", tag("MAP"), PacketHeader::ACK),
		p_recv("MAP", tag("MAP_ACK"), bind(&WaitSync::setMap, this, _1), PacketHeader::MAP_IS),
		p_send("MAP_ACK", tag("TOKEN"), PacketHeader::ACK),
		p_recv("TOKEN", tag("TOKEN_ACK"), bind(&WaitSync::setTokens, this, _1), PacketHeader::CIRCULAR_TOKENS),
		p_send("TOKEN_ACK", tag("SV"), PacketHeader::ACK),
		p_if_recv(
			"SV",
			p_recv("DEV_CARDS", tag("NO_DEVS"), PacketHeader::DEV_CARDS),
			p_recv("TURN", tag("TURN_ACK"), bind(&WaitSync::setTurn, this, _1), {PacketHeader::YOU_START, PacketHeader::I_START})
			),
		p_send("NO_DEVS", tag("TURN"), PacketHeader::NO),
		p_send("TURN_ACK", tag(PROTOCOL_DONE), ACK)
	);

	/* Creo el evento */
	this->event = new SyncEvent(CatanEvent::Sources::NETWORKING);
}

WaitSync::
~WaitSync() {
	delete syncProtocol;
}

void
WaitSync::run() {

	NetworkSocket* socket = networking.getSocket();

	if (socket->hasReceived()) {

		NetworkPacket* packet = socket->receive();

		syncProtocol->recv(packet);

		switch (syncProtocol->getStatus()) {
		case ProtocolStatus::DONE:
			networking.getGame().handle(event);
			networking.changeState(new Idle(networking));
			break;
		case ProtocolStatus::PROTOCOL_ERROR:
			networking.setError("WaitSync - Hubo un error en el protocolo de sincronizacion!");
			networking.changeState(new NetError(networking));
			break;
		case ProtocolStatus::TIMEOUT:
			networking.setError("WaitSync - Hubo timeout por demasiada espera en el protocolo!");
			networking.changeState(new NetError(networking));
			break;
		}
	}
}

void
WaitSync::update() {}

string
WaitSync::what() {	return string("WAITING_SYNC");	}

NetworkPacket* 
WaitSync::getLocalName(void) {
	/* Busco el nombre local */
	string localName = "Lucas";
	event->setLocalName(localName);

	/* Armo y devuelvo paquete */
	return new NamePacket(localName);
}

void 
WaitSync::setRemoteName(NetworkPacket* packet) {
	/* Recibo el nombre */
	string remoteName = ((NamePacket*)packet)->getName();

	/* Guardo el nombre en el evento */
	event->setRemoveName(remoteName);
}

void 
WaitSync::setMap(NetworkPacket* packet) {
	/* Recibo el mapa */
	MapData map = ((MapPacket*)packet)->getMap();

	/* Guardo el mapa en el evento */
	event->setMap(map);
}

void 
WaitSync::setTokens(NetworkPacket* packet) {
	/* Recibo los tokens */
	TokenData tokens = ((TokenPacket*)packet)->getTokens();

	/* Guardo los tokens */
	event->setTokens(tokens);
}

void 
WaitSync::setTurn(NetworkPacket* packet) {
	/* Recibo el turno */
	PlayerId turn = packet->getHeader() == PacketHeader::YOU_START ? PlayerId::PLAYER_ONE : PlayerId::PLAYER_TWO;

	/* Guardo el turno */
	event->setTurn(turn);
}