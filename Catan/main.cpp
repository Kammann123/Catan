#include "CatanNetworking/NetworkParsers/NetworkParser.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

	NetworkParser parser;
	unsigned char stream[] = {
		0x01,
		0x10,
		0x11, 3, 'T', 'O', 'M'
	};

	for (unsigned char c : stream) {
		parser.parse(c);

		if (parser.getStatus() != NetworkParser::Status::OK) {
			cout << parser.getError() << endl;
			getchar();
			return -1;
		}
	}

	while (parser.hasPackets()) {

		NetworkPacket* packet = parser.getNextPacket();
	}
}