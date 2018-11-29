#include "TellEnd.h"

TellEnd::
TellEnd(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::TELL_END) {
	/* Defino el protocolo */
	Protocol* tellEndProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"I_WON",
		TIMEOUT_TIME,
		p_send("I_WON", tag("REMOTE_DECIDE"), PacketHeader::I_WON),
		p_if_recv("REMOTE_DECIDE",
			p_recv("WANTS_AGAIN", tag("AGAIN_ANSWER"), bind(&TellEnd::playAgain, this, _1), PacketHeader::PLAY_AGAIN),
			p_recv("WANTS_OVER", tag("OVER_ACK"), bind(&TellEnd::gameOver, this, _1), PacketHeader::GAME_OVER),
			),
		p_send("OVER_ACK", tag(PROTOCOL_DONE), PacketHeader::ACK),
		p_if_send("AGAIN_ANSWER",
			p_wait_send("ANSWER_OK", tag("OK_ACK"), bind(&TellEnd::askSync, this, _1), PacketHeader::PLAY_AGAIN),
			p_wait_send("ANSWER_NO", tag("NO_ACK"), PacketHeader::GAME_OVER)
		),
		p_recv("NO_ACK", tag(PROTOCOL_DONE), bind(&TellEnd::confirm, this, _1), PacketHeader::ACK),
		p_recv("OK_ACK", tag("SEND_MAP"), bind(&TellEnd::confirm, this, _1), PacketHeader::ACK),
		p_data_send("SEND_MAP", tag("MAP_ACK"), bind(&TellEnd::getMap, this)),
		p_recv("MAP_ACK", tag("SEND_TOKEN"), PacketHeader::ACK),
		p_data_send("SEND_TOKEN", tag("TOKEN_ACK"), bind(&TellEnd::getTokens, this)),
		p_recv("TOKEN_ACK", cond_tag(bind(&TellEnd::whoStarts, this), "MY_TURN", "YOUR_TURN"), PacketHeader::ACK),
		p_send("YOUR_TURN", tag(PROTOCOL_DONE), PacketHeader::YOU_START),
		p_send("MY_TURN", tag("TURN_ACK"), PacketHeader::I_START),
		p_recv("TURN_ACK", tag(PROTOCOL_DONE), bind(&TellEnd::confirm, this, _1), PacketHeader::ACK)
	);
	this->setProtocol(tellEndProtocol);
}	

void 
TellEnd::askSync(NetworkPacket* packet) { 
	networking.getGame().handle(new CatanEvent(CatanEvent::Events::ASK_SYNC, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO)); 
}

void
TellEnd::gameOver(NetworkPacket* packet) { 
	confirm(packet);
	networking.getGame().syncHandle(new CatanEvent(CatanEvent::Events::GAME_OVER, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO));
}

void
TellEnd::playAgain(NetworkPacket* packet) {
	confirm(packet);
	networking.getGame().syncHandle(new CatanEvent(CatanEvent::Events::PLAY_AGAIN, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO));
}

NetworkPacket*
TellEnd::getMap(void) { 
	return new MapPacket(networking.getGame().getMap()); 
}

NetworkPacket*
TellEnd::getTokens(void) { 
	return new TokenPacket(networking.getGame().getTokens()); 
}

bool
TellEnd::whoStarts(void) { 
	return networking.getGame().getTurn() == PlayerId::PLAYER_ONE; 
}