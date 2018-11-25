#pragma once

#include "HandshakingState.h"
#include "../../CatanEvents/SyncEvent.h"

class WaitSync : public HandshakingState {
public:
	WaitSync(CatanNetworking& net) : HandshakingState(waitSyncProtocol, net) { this->event = new SyncEvent(CatanEvent::Sources::NETWORKING); }
	string what(void) { return "CLIENT_WAIT_SYNC"; }
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::NAME; }
private:
	/* Metodos del protocolo */
	NetworkPacket * getLocalName(void) { return new NamePacket(networking.getGame().getLocalName()); }
	void setRemoteName(NetworkPacket* packet) { event->setRemoteName(((NamePacket*)packet)->getName()); }
	void setMap(NetworkPacket* packet) { event->setMap(((MapPacket*)packet)->getMap()); }
	void setTokens(NetworkPacket* packet) { event->setTokens(((TokenPacket*)packet)->getTokens()); }
	void setTurn(NetworkPacket* packet) { 
		event->setTurn(packet->getHeader() == PacketHeader::YOU_START ? PlayerId::PLAYER_ONE : PlayerId::PLAYER_TWO);
		event->setDevMode(false);
		networking.getGame().handle(this->event);
	}
	bool doIStart(void) { return networking.getGame().getTurn() == PlayerId::PLAYER_ONE; }

	/* Protocolo */
	SyncEvent* event;

	Protocol * waitSyncProtocol = protocol(
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
			p_recv("TURN", cond_tag(bind(&WaitSync::doIStart, this), PROTOCOL_DONE, "TURN_ACK"), bind(&WaitSync::setTurn, this, _1), { PacketHeader::YOU_START, PacketHeader::I_START })
		),
		p_send("NO_DEVS", tag("TURN"), PacketHeader::NO),
		p_send("TURN_ACK", tag(PROTOCOL_DONE), ACK)
	);
};