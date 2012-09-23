#ifndef R_BITSEQUENCE_HPP
#define R_BITSEQUENCE_HPP

#include <string>
#include <vector>
#include <cmath>
#include <iostream>


class rBitSequence{
public:
	rBitSequence();
	rBitSequence(const rBitSequence& sequence);
	rBitSequence(char* buffer , size_t numBits);
	rBitSequence(std::istream& stream , size_t numBits);

	void Assign(const rBitSequence& sequence);
	void Assign(char* buffer , size_t numBits);
	void Assign(std::istream& stream , size_t numBits);

	void AppendInt(int value , size_t numBits = sizeof (int) * 8);
	virtual size_t Append(char* buffer, size_t bufferSize , size_t numBits);

	int Read(char* dest , size_t index , size_t numBits);
	
	void AppendSequence(const rBitSequence& sequence);

	inline size_t Length() const;
	inline size_t NumBytes() const;
	inline bool IsEmpty() const;
	
	bool GetBit(size_t index) const;
	int SetBit(size_t index , bool value);
	int ToggleBit(size_t index);

	void Clear();

	void AppendOne();
	void AppendOnes(size_t amount);
	
	void AppendZero();
	void AppendZeros(size_t amount);

	std::string GetString() const;

	rBitSequence& operator =(const rBitSequence& sequence);
	rBitSequence& operator +=(const rBitSequence& sequence);
	rBitSequence& operator <<(const rBitSequence& sequence);

	void WriteToStream(std::ostream& stream);

private:

	void CreateNewByte();
	void CheckForNewByte();
	
	void WriteValue(char* value , size_t numBytes);
	void WritePartialValue(char* value , size_t numBits);
	
	void WriteByte(char value, size_t num_bytes);
	
private:
	std::vector<char> m_container;
	size_t m_length;

	size_t m_insertionByte;
	int m_insertionBit;
};

size_t rBitSequence::Length() const{
	return m_length;
}

bool rBitSequence::IsEmpty() const{
	return m_container.size() == 0;
}

size_t rBitSequence::NumBytes() const{
	return m_container.size();
}

#endif
