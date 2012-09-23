#include "rLzwDecoder.hpp"

rLzwDecoder::rLzwDecoder(){
	InitDict();
}

void rLzwDecoder::InitDict(){
	m_codeSize = 9;
	m_nextCodeId = 0;
	
	for (unsigned int i = 0; i < 256U; i++){
		std::string s(1, char(i));
		AddDictionaryEntry(s);
	}	
}

void rLzwDecoder::AddDictionaryEntry(const std::string& str){
	// if (m_nextCodeId > 255)
		// std::cout << "new entry:\tcode: " << m_nextCodeId << "\tentry: " << str<<std::endl;
	
	rLzwDecoderDictEntry entry(m_nextCodeId, str);
	m_dictionary.insert(entry);
	
	IncrementNextCodeId();
}

int rLzwDecoder::Decode(rBitStreamIn& in, std::ostream& out){
	unsigned int streamSize = in.NumBits();
	unsigned int bitsRead = 0;
	
	unsigned int code, nextCode;
	
	while (bitsRead < streamSize){
		code = nextCode = 0;
		
		bitsRead += in.Read((char*)&code, m_codeSize);
		in.Peek((char*)&nextCode, m_codeSize);
		
		// std::cout << "code:\t" << code << "\tstring:"<<m_dictionary[code] <<"\tnextCode:\t"<<nextCode<<"\tsize:\t"<<m_codeSize<<std::endl;
		
		WriteCodeOut(code, out);
		std::string entry = m_dictionary[code] + m_dictionary[nextCode][0];
		AddDictionaryEntry(entry);
	}
}

void rLzwDecoder::WriteCodeOut(unsigned int code, std::ostream& out){
	std::string& str = m_dictionary[code];
	out.write(str.c_str() , str.size());
}

