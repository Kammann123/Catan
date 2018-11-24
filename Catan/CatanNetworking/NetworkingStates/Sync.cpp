#include "Sync.h"

#include "../../CatanGame/Player.h"
#include "../CatanNetworking.h"

#include "Idle.h"
#include "NetError.h"

Sync::
Sync(CatanNetworking& networking) : NetworkingState(networking) {

	/* Creamos el protocolo de sincronizacion */
	this->syncProtocol = protocol(
		socket_send(networking.getSocket()),
		"REMOTE_NAME",
		p_send("REMOTE_NAME", tag("GET_REMOTE"), NAME),
		p_recv("GET_REMOTE", tag("REMOTE_ACK"), bind(&Sync::setRemoteName, this, _1), NAME_IS),
		p_send("REMOTE_ACK", tag("LOCAL_NAME"), ACK),
		p_recv("LOCAL_NAME", tag("SEND_NAME"), NAME),
		p_data_send("SEND_NAME", tag("SEND_ACK"), bind(&Sync::getLocalName, this)),
		p_recv("SEND_ACK", tag("SEND_MAP"), ACK),
		p_data_send("SEND_MAP", tag("MAP_ACK"), bind(&Sync::getMap, this)),
		p_recv("MAP_ACK", tag("SEND_TOKEN"), ACK),
		p_data_send("SEND_TOKEN", tag("TOKEN_ACK"), bind(&Sync::getTokens, this)),
		p_recv("TOKEN_ACK", tag("SEND_TURN"), ACK),
		p_data_send("SEND_TURN", tag("TURN_ACK"), bind(&Sync::getTurn, this)),
		p_recv("TURN_ACK", tag(PROTOCOL_DONE), ACK)
	);
}

Sync::
~Sync() {
	if (syncProtocol) {
		delete syncProtocol;
	}
}

void 
Sync::run(void) {

	NetworkSocket* socket = networking.getSocket();

	if (socket->hasReceived()) {

		NetworkPacket* packet = socket->receive();

		this->syncProtocol->recv(packet);

		switch (this->syncProtocol->getStatus()) {
			case ProtocolStatus::DONE:
				networking.changeState(new Idle(networking));
				break;
			case ProtocolStatus::PROTOCOL_ERROR:
				networking.setError("SyncProtocol - Hubo un error en el protocolo de comunicacion1");
				networking.changeState(new NetError(networking));
				break;
			case ProtocolStatus::TIMEOUT:
				networking.setError("SyncProtocol - Demasiado tiempo de espera en el protocolo!");
				networking.changeState(new NetError(networking));
				break;
		}
	}
}

void 
Sync::update(void) {}

string 
Sync::what(void) {	return "SERVER_SYNC";	}

void 
Sync::setRemoteName(NetworkPacket* packet) {
	/* Recupero el nombre remoto */
	string remoteName = ((NamePacket*)packet)->getName();

	/* Lo configuro en catan game */

}

NetworkPacket* 
Sync::getLocalName(void) {
	/* Busco el nombre local en catan game */
	string localName = "Lucas";

	/* Armo el paquete y devuelvo */
	return new NamePacket(localName);
}

NetworkPacket* 
Sync::getMap(void) {
	/* Busco el mapa en catan game */
	MapData map;

	/* Armo el paquete y devuelvo */
	return new MapPacket(map.getMap());
}

NetworkPacket* 
Sync::getTokens(void) {
	/* Busco los tokens en catan game */
	TokenData tokens;

	/* Armo el paquete y lo devuelvo */
	return new TokenPacket(tokens.getTokens());
}

NetworkPacket* 
Sync::getTurn(void) {
	/* Busco el turno actual */
	PlayerId turn;

	/* Armo el paquete y lo devuelvo */
	PacketHeader header = turn == PlayerId::PLAYER_ONE ? PacketHeader::I_START : PacketHeader::YOU_START;
	return new NetworkPacket(header);
}