#pragma once

#include "HandshakingState.h"

class ListenEnd : public HandshakingState {
public:
	ListenEnd(CatanNetworking& net) : HandshakingState(listenEndProtocol, net) {}
	string what(void) { return "LISTEN_END";  }
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::I_WON; }
private:
	/* Metodos del protocolo */
	void userWon(NetworkPacket* packet) { networking.getGame().handle( new CatanEvent(CatanEvent::Events::WON, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO) ); }
	void gameOver(NetworkPacket* packet) { networking.getGame().handle( new CatanEvent(CatanEvent::Events::GAME_OVER, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO) ); }
	void playAgain(NetworkPacket* packet) { networking.getGame().handle(new CatanEvent(CatanEvent::Events::PLAY_AGAIN, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO)); }
	void setMap(NetworkPacket* packet) { /* networking.getGame().setMap(((MapPacket*)packet)->getMap()); */ }
	void setTokens(NetworkPacket* packet) { /* networking.getGame().setTokens(((TokenPacket*)packet)->getTokens(); */ }
	void setTurn(NetworkPacket* packet) {
		/* networking.getGame().setTurn(packet->getHeader() == PacketHeader::YOU_START ? PlayerId::PLAYER_ONE : PlayerID::PLAYER_TWO); */
		/* networking.getGame().handle(this->event); */
	}
	bool doIStart(void) { return true;/* return networking.getGame().getTurn() == PlayerId::PLAYER_ONE; */ }

	/* Protocolo */
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
			p_recv("ANSWER_OK", tag("RECV_MAP"), PacketHeader::PLAY_AGAIN),
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
};