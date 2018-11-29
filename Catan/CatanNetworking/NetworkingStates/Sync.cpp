#include "Sync.h"

Sync::
Sync(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::SYNC) {
	/* Defino el protocolo */
	Protocol * syncProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"REMOTE_NAME",
		TIMEOUT_TIME,
		p_send("REMOTE_NAME", tag("GET_REMOTE"), NAME),
		p_recv("GET_REMOTE", tag("REMOTE_ACK"), bind(&Sync::setRemoteName, this, _1), NAME_IS),
		p_send("REMOTE_ACK", tag("LOCAL_NAME"), ACK),
		p_recv("LOCAL_NAME", tag("SEND_NAME"), NAME),
		p_data_send("SEND_NAME", tag("SEND_ACK"), bind(&Sync::getLocalName, this)),
		p_recv("SEND_ACK", tag("SEND_MAP"), ACK),
		p_data_send("SEND_MAP", tag("MAP_ACK"), bind(&Sync::getMap, this)),
		p_recv("MAP_ACK", tag("SEND_TOKEN"), ACK),
		p_data_send("SEND_TOKEN", tag("TOKEN_ACK"), bind(&Sync::getTokens, this)),
		p_recv("TOKEN_ACK", cond_tag(bind(&Sync::whoStarts, this), "I_START", "YOU_START"), ACK),
		p_send("I_START", tag("TURN_ACK"), PacketHeader::I_START),
		p_recv("TURN_ACK", tag(PROTOCOL_DONE), ACK),
		p_send("YOU_START", tag(PROTOCOL_DONE), PacketHeader::YOU_START)
	);
	this->setProtocol(syncProtocol);
}

void
Sync::setRemoteName(NetworkPacket* packet) { 
	networking.getGame().setRemoteName(((NamePacket*)packet)->getName()); 
}

NetworkPacket*
Sync::getLocalName(void) { 
	return new NamePacket(networking.getGame().getLocalName()); 
}

NetworkPacket*
Sync::getMap(void) { 
	return new MapPacket(networking.getGame().getMap()); 
}

NetworkPacket*
Sync::getTokens(void) { 
	return new TokenPacket(networking.getGame().getTokens()); 
}

bool
Sync::whoStarts(void) { 
	return networking.getGame().getTurn() == PlayerId::PLAYER_ONE; 
}
