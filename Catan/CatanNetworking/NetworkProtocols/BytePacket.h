#pragma once

/*
* BytePacket
* Paquete de datos a enviar como secuencia de Bytes
*/
class BytePacket {
public:
	BytePacket(unsigned char* _bytes, unsigned int _length) : bytes(_bytes), length(_length) {}
	unsigned char* getBytes(void) { return this->bytes; }
	unsigned int getLength(void) { return this->length; }
	void releaseBytes(void) { delete[] bytes; }
private:
	unsigned char* bytes;
	unsigned int length;
};