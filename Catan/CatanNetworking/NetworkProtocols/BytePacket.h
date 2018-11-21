#pragma once

/*
* BytePacket
* Paquete de datos a enviar como secuencia de Bytes
*/
class BytePacket {
public:
	/* Constructor del paquete de bytes */
	BytePacket(unsigned char* _bytes, unsigned int _length) : bytes(_bytes), length(_length) {}

	/*
	* getBytes
	* Devuelve los bytes del mensaje
	*/
	unsigned char* getBytes(void) { return this->bytes; }

	/*
	* getLength
	* Devuelve el largo total de la cadena de bytes
	*/
	unsigned int getLength(void) { return this->length; }

	/*
	* releaseBytes
	* Libera la memoria ocupada por la cadena que forma el paquete de bytes
	*/
	void releaseBytes(void) { delete[] bytes; }

private:
	unsigned char* bytes;
	unsigned int length;
};