#ifndef R_BITSEQUENCE_READER_HPP
#define R_BITSEQUENCE_READER_HPP

#include "rBitSequence.hpp"
#include "rBitStreams.hpp"

class rBitSequenceReader : public rBitStreamIn{
public:
	rBitSequenceReader(rBitSequence* seq);
	
	void Assign(rBitSequence* seq);
	
	virtual size_t Read(char* dest, size_t numBits);
	virtual size_t Peek(char* dest, size_t numBits);
	virtual size_t NumBits() const;
	
private:
	size_t m_readPos;
	rBitSequence* m_sequence;
};

class rBitSequenceWriter : public rBitStreamOut {
public:
	rBitSequenceWriter(rBitSequence* seq);
	
	void Assign(rBitSequence* seq);
	
	virtual size_t Write(char* buffer, size_t bufferSize , size_t numBits);
	
private:
	size_t m_bytesWritten;
	rBitSequence* m_sequence;
};

#endif
