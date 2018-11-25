#pragma once

#include "HandshakingState.h"

class Sync : public HandshakingState {
public:
	Sync(CatanNetworking net) : HandshakingState(syncProtocol, net) {}
	string what(void) { return "SERVER_SYNC"; }
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::NAME; }
private:
	/* Metodos del protocolo */
	void setRemoteName(NetworkPacket* packet) { /* networking.getGame().setRemoteName(((NamePacket*)packet)->getName()); */ }
	NetworkPacket* getLocalName(void) { return nullptr;/* return new NamePacket(networking.getGame().getLocalName()); */ }
	NetworkPacket* getMap(void) { return nullptr;/* return new MapPacket(networking.getGame().getMap()); */ }
	NetworkPacket* getTokens(void){ return nullptr;/* return new TokenPacket(networking.getGame().getTokens()); */ }
	bool whoStarts(void) { return true;/* return networking.getGame().getTurn() == PlayerId::PLAYER_ONE; */ }

	/* Protocolo */
	Protocol * syncProtocol = protocol(
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
		p_recv("TOKEN_ACK", cond_tag(bind(&Sync::whoStarts, this), "I_START", "YOU_START"), ACK),
		p_send("I_START", tag("TURN_ACK"), PacketHeader::I_START),
		p_recv("TURN_ACK", tag(PROTOCOL_DONE), ACK),
		p_send("YOU_START", tag(PROTOCOL_DONE), PacketHeader::YOU_START)
	);
};