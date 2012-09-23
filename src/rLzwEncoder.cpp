#include "rLzwEncoder.hpp"

rLzwEncoder::rLzwEncoder(){
	InitDict();
}

bool rLzwEncoder::PopulateBufferAndSearchStrings(std::istream& in, std::string& buffer , std::string& search){
	char g, p;
	buffer.clear();
	search.clear();
	
	do{
		g = in.get();
		
		if (!in.good())
			return false;
		
		p = in.peek();   
		buffer.append(1, g);
		search = buffer + p;
		
	}while(m_dictionary.count(search)  && in.good());
	
	// std::cout << "code: " << m_nextCodeId << "\tbuffer: " << buffer <<"\tsearch: "<<search<<std::endl;
	
	return true;
	
}

int rLzwEncoder::Encode(std::istream& in, rBitStreamOut& out){
	std::string buffer;
	std::string search;
	
	while (in){
		bool write = PopulateBufferAndSearchStrings(in, buffer, search);
		
		if (write){
			WriteInfoToOutStream(m_dictionary[buffer] , out);
			AddDictionaryEntry(search);
		}
	}
	
	
	CloseArchiveStream(out);
}

void rLzwEncoder::CloseArchiveStream(rBitStreamOut& out){
}

void rLzwEncoder::WriteInfoToOutStream(unsigned int code, rBitStreamOut& out){
	out.Write( (char*)&code , 4, m_codeSize);
}

void rLzwEncoder::InitDict(){
	m_dictionary.clear();
	
	m_codeSize = 8;
	m_nextCodeId = 0;
	
	for (unsigned int i = 0; i < 256U; i++){
		std::string s(1, char(i));
		AddDictionaryEntry(s);
	}
}


int rLzwEncoder::AddDictionaryEntry(const std::string& key){
	if (m_dictionary.count(key))
		return false;
	
	m_dictionary[key] = m_nextCodeId;
	
	IncrementNextCodeId();
	
	return true;
}

