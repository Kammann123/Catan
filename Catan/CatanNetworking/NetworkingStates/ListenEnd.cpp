#include "ListenEnd.h"

ListenEnd::
ListenEnd(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::LISTEN_END) {
	/* Creo el protocolo, lo defino y lo agrego */
	Protocol* listenEndProtocol = protocol(
		socket_send(networking.getSocket()),
		"WAIT_WON",
		p_recv("WAIT_WON", tag("DECIDE"), PacketHeader::I_WON),
		p_if_send("DECIDE",
			p_wait_send("DECIDE_AGAIN", tag("AGAIN_ANSWER"), PacketHeader::PLAY_AGAIN),
			p_wait_send("DECIDE_OVER", tag("OVER_ACK"), PacketHeader::GAME_OVER)
		),
		p_recv("OVER_ACK", tag(PROTOCOL_DONE), PacketHeader::ACK),
		p_if_recv("AGAIN_ANSWER",
			p_recv("ANSWER_OK", tag("RECV_MAP"), bind(&ListenEnd::createEvent, this, _1),PacketHeader::PLAY_AGAIN),
			p_recv("ANSWER_NO", tag("NO_ACK"), PacketHeader::GAME_OVER)
		),
		p_send("NO_ACK", tag(PROTOCOL_DONE), PacketHeader::ACK),
		p_recv("RECV_MAP", tag("MAP_ACK"), bind(&ListenEnd::setMap, this, _1), PacketHeader::MAP_IS),
		p_send("MAP_ACK", tag("RECV_TOKEN"), PacketHeader::ACK),
		p_recv("RECV_TOKEN", tag("TOKEN_ACK"), bind(&ListenEnd::setTokens, this, _1), PacketHeader::CIRCULAR_TOKENS),
		p_send("TOKEN_ACK", tag("TURN"), PacketHeader::ACK),
		p_if_recv("TURN",
			p_recv("MY_TURN", tag(PROTOCOL_DONE), bind(&ListenEnd::setTurn, this, _1), PacketHeader::YOU_START),
			p_recv("HIS_TURN", tag("TURN_ACK"), bind(&ListenEnd::setTurn, this, _1), PacketHeader::I_START)
		),
		p_send("TURN_ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(listenEndProtocol);
}

void
ListenEnd::userWon(NetworkPacket* packet) { 
	networking.getGame().handle(new CatanEvent(CatanEvent::Events::WON, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO)); 
}

void
ListenEnd::gameOver(NetworkPacket* packet) { 
	networking.getGame().handle(new CatanEvent(CatanEvent::Events::GAME_OVER, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO)); 
}

void
ListenEnd::playAgain(NetworkPacket* packet) { 
	networking.getGame().handle(new CatanEvent(CatanEvent::Events::PLAY_AGAIN, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO)); 
}

void
ListenEnd::setMap(NetworkPacket* packet) { 
	event->setMap(((MapPacket*)packet)->getMap()); 
}

void
ListenEnd::setTokens(NetworkPacket* packet) { 
	event->setTokens(((TokenPacket*)packet)->getTokens()); 
}

void
ListenEnd::setTurn(NetworkPacket* packet) {
	event->setTurn(packet->getHeader() == PacketHeader::YOU_START ? PlayerId::PLAYER_ONE : PlayerId::PLAYER_TWO);
	networking.getGame().handle(event);
}

bool
ListenEnd::doIStart(void) { 
	return networking.getGame().getTurn() == PlayerId::PLAYER_ONE; 
}

void
ListenEnd::createEvent(NetworkPacket* packet) {
	this->event = new SyncEvent(CatanEvent::Sources::NETWORKING);
}