#ifndef R_BITSTREAM_IN_HPP
#define R_BITSTREAM_IN_HPP

class rBitStreamIn{
public:
	virtual size_t Read(char* dest, size_t numBits) = 0;
	virtual size_t Peek(char* dest, size_t numBits) = 0;
	virtual size_t NumBits() const = 0;
};

class rBitStreamOut{
public:
	virtual size_t Write(char* buffer, size_t bufferSize , size_t numBits) = 0;
};

#endif
