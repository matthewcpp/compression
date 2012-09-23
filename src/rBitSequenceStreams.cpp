#include "rBitSequenceStreams.hpp"

rBitSequenceReader::rBitSequenceReader(rBitSequence* seq){
	Assign(seq);
}

void rBitSequenceReader::Assign(rBitSequence* seq){
	m_readPos = 0;
	m_sequence = seq;
}

size_t rBitSequenceReader::Read(char* dest, size_t numBits){
	size_t result = m_sequence->Read(dest, m_readPos , numBits);
	m_readPos += result;
	return result;
}

size_t rBitSequenceReader::Peek(char* dest, size_t numBits){
	size_t result = m_sequence->Read(dest, m_readPos , numBits);
	return result;
}

size_t rBitSequenceReader::NumBits() const{
	return m_sequence->Length();
}


rBitSequenceWriter::rBitSequenceWriter(rBitSequence* seq){
	Assign(seq);
}

void rBitSequenceWriter::Assign(rBitSequence* seq){
	m_bytesWritten = 0;
	m_sequence = seq;
}

size_t rBitSequenceWriter::Write(char* buffer, size_t bufferSize , size_t numBits){
	size_t result = m_sequence->Append(buffer, bufferSize, numBits);
	m_bytesWritten += result;
	return result;
}
