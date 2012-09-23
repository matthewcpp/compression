#include "rBitSequence.hpp"

rBitSequence::rBitSequence(){
	Clear();
}

rBitSequence::rBitSequence(const rBitSequence& sequence){
	Assign(sequence);
}

rBitSequence::rBitSequence(char* buffer , size_t numBits){
	Assign (buffer , numBits);
}

rBitSequence::rBitSequence(std::istream& stream , size_t numBits){
	Assign (stream , numBits);
}

void rBitSequence::Assign(const rBitSequence& sequence){
	m_container = sequence.m_container;
	m_length = sequence.m_length;
	m_insertionBit = sequence.m_insertionBit;
	m_insertionByte = sequence.m_insertionByte;
}

void rBitSequence::Assign(std::istream& stream , size_t numBits){
	if (!stream.good()){
		Clear();
		return;
	}

	int bytes = numBits / 8;
	int bits = numBits % 8;

	m_container.resize(bytes);
	m_insertionByte = bytes > 0 ? bytes -1 : 0;
	m_insertionBit = 8;
	m_length = bytes * 8;
	
	if (bytes > 0)
		stream.read(&m_container[0] , bytes);

	if (bits > 0){
		char nextByte;
		stream.get(nextByte);
		WriteByte (nextByte , bits);
	}	
}

void rBitSequence::Assign(char* buffer , size_t numBits){
	int bytes = numBits / 8;
	int bits = numBits % 8;

	m_container.resize(bytes);
	m_insertionByte = bytes > 0 ? bytes -1 : 0;
	m_insertionBit = 8;
	m_length = bytes * 8;
	
	if (bytes > 0)
		memcpy(&m_container[0], buffer , bytes);

	if (bits > 0)
		WriteByte (buffer[bytes] , bits);
}

rBitSequence& rBitSequence::operator =(const rBitSequence& sequence){
	Assign(sequence);
	return *this;
}

rBitSequence& rBitSequence::operator +=(const rBitSequence& sequence){
	AppendSequence(sequence);
	return *this;
}

rBitSequence& rBitSequence::operator <<(const rBitSequence& sequence){
	AppendSequence(sequence);
	return *this;
}

void rBitSequence::Clear(){
	m_container.clear();
	m_length = 0;
	m_insertionBit = 8;
}

void rBitSequence::CheckForNewByte(){
	if (m_insertionBit == 8)
		CreateNewByte(); 
}

void rBitSequence::CreateNewByte(){
	m_container.push_back(0);
	m_insertionBit = 0;
	m_insertionByte = m_container.size() -1;
}

void rBitSequence::AppendZeros(size_t amount){
	for (size_t i = 0; i < amount; i++)
		AppendZero();
}

void rBitSequence::AppendOnes(size_t amount){
	for (size_t i = 0; i < amount; i++)
		AppendOne();
}

void rBitSequence::AppendOne(){
	CheckForNewByte();

	char mask = 1U << m_insertionBit;
	m_container[m_insertionByte] |= mask;
	m_insertionBit++;
	m_length++;
}

void rBitSequence::AppendZero(){
	CheckForNewByte();

	m_insertionBit++;
	m_length++;	
}

void rBitSequence::WriteByte(char value, size_t num_bytes){
	char mask;
	
	for (int bit = 0; bit < num_bytes; bit++){
		mask = 1U << bit;


		if ( (mask & value) == mask)
			AppendOne();
		else
			AppendZero();
	}
}

void rBitSequence::WriteValue(char* value , size_t numBytes){
	
	for (int byte = 0; byte < numBytes; byte++)
		WriteByte(value[byte], 8 );

}

void rBitSequence::WritePartialValue(char* value , size_t numBits){
	int byteIndex = 0;
	int bitsRemaining = numBits;
	int bitsToWrite;
	
	while (bitsRemaining > 0){
		bitsToWrite = bitsRemaining > 8 ? 8 : bitsRemaining;
		
		WriteByte(value[byteIndex] , bitsToWrite);
		
		bitsRemaining -= bitsToWrite;
		byteIndex++;
	}
	
}

size_t rBitSequence::Append(char* buffer, size_t bufferSize , size_t numBits){
	size_t bufferBitSize = bufferSize * 8;

	if ( numBits > bufferSize * 8){
		AppendZeros( numBits - bufferBitSize );
		WriteValue(buffer , bufferSize);
	}
	else if (numBits == bufferBitSize)
		WriteValue(buffer , bufferSize);
	else
		WritePartialValue(buffer , numBits);
	
	return numBits;
}

void rBitSequence::AppendInt(int value, size_t numBits){

	if ( numBits > sizeof (int) * 8){
		AppendZeros( numBits - (sizeof (int) * 8 ) );
		WriteValue((char*)&value , sizeof(int));
	}
	else if (numBits == sizeof (int) * 8)
		WriteValue((char*)&value , sizeof(int));
	else
		WritePartialValue((char*)&value , numBits);
}

void rBitSequence::AppendSequence(const rBitSequence& sequence){

	for (size_t i = 0; i < sequence.Length(); i++){
		if (sequence.GetBit(i))
			AppendOne();
		else
			AppendZero();
	}
}

int rBitSequence::ToggleBit(size_t index){
	if (index >= m_length)
		return 0;

	size_t byte = index / 8;
	size_t bit = index % 8;
	
	char mask = 1U << bit; 

	m_container[byte] ^= mask;

	return 1;
}

bool rBitSequence::GetBit(size_t index) const{
	if (index >= m_length)
		return false;

	size_t byte = index / 8;
	char bit = index % 8;

	char mask = 1U << bit;

	return ( (m_container[byte] & mask) == mask);
}

int rBitSequence::SetBit(size_t index , bool value){

	if (index >= m_length)
		return false;

	size_t byte = index / 8;
	size_t bit = index % 8;
	char mask = 1U << bit;

	if (value)
		m_container[byte] |= mask;
	
	else
		m_container[byte] &= ~mask;	
	

	return true;
}

void rBitSequence::WriteToStream(std::ostream& stream){
	stream.write(&m_container[0] , m_container.size());
}


int rBitSequence::Read(char* dest , size_t index ,size_t numBits){
	size_t bitsRead = 0;
	
	bool value;
	char mask;
	
	size_t writeByte = 0;
	size_t writeBit = 0;

	while (bitsRead < numBits && index < m_length){
		value = GetBit(index);

		if (value){
			mask = 1U << writeBit;
			dest[writeByte] |= mask;
		}

		
		index++;
		bitsRead++;
		writeBit++;
		
		if (writeBit == 8){
			writeByte++;
			writeBit = 0;
		}
		
	}

	return bitsRead;
}

std::string rBitSequence::GetString() const{
	std::string str;
	size_t bit = 0;
	unsigned char mask;

	for (size_t byte = 0; byte < m_container.size(); byte++){

		for (int b = 0; b < 8; b++){
			mask = 1U << b;

			if ( (mask & m_container[byte]) == mask)
				str += '1';
			else
				str += '0';


			bit++;
			if (bit == m_length)
				return str;

			if (bit > 0 && bit % 8 == 0)
				str += ' ';
		}
	}

	return str;
}
