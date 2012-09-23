#ifndef R_LZWENCODER_HPP
#define R_LZWENCODER_HPP

#include <istream>
#include <iostream>
#include <map>
#include <string>

#include "rBitStreams.hpp"
#include "rLzwBase.hpp"

typedef std::map < std::string , unsigned int > rLzwDict;
typedef rLzwDict::iterator rLzwDictItr;
typedef std::pair < std::string , unsigned int > rLzwDictEntry;


class rLzwEncoder : public rLzwBase{
public:
	rLzwEncoder();	
	
	int Encode(std::istream& in, rBitStreamOut& out);
	
private:
	
	void InitDict();
	
	int AddDictionaryEntry(const std::string& str);
	
	bool PopulateBufferAndSearchStrings(std::istream& in, std::string& buffer , std::string& search);
	void WriteInfoToOutStream(unsigned int code, rBitStreamOut& out);
	void CloseArchiveStream(rBitStreamOut& out);
	
private:	
	rLzwDict m_dictionary;
	
};

#endif
