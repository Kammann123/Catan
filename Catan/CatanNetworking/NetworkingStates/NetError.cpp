#include "NetError.h"

#include "../NetworkPackets/NetworkPacket.h"
#include "../CatanNetworking.h"

NetError::
NetError(CatanNetworking& networking) : NetworkingState(networking) {
	/* Se transmite un mensaje de error al otro extremo de la comunicacion
	* en caso de que se posea un socket abierto, y luego se determina un estado
	* de espera y error. Deshabilitando el Networking.
	*/
	if( networking.getSocket() )
		networking.getSocket()->send(new NetworkPacket(PacketHeader::HEADER_ERROR)); 
	networking.setError("NetError - Networking Error, ha dejado de funcionar la comunicacion.");
}

void
NetError::run() {}

void
NetError::update() {}

string
NetError::what() {	return string("NET_ERROR");}