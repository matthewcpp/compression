#ifndef R_LZWDECODER_HPP
#define R_LZWDECODER_HPP

#include <map>
#include <string>
#include <iostream>

#include "rLzwBase.hpp"
#include "rBitStreams.hpp"

typedef std::map <int , std::string> rLzwDecoderDict;
typedef rLzwDecoderDict::iterator rLzwDecoderDictItr;
typedef std::pair <int , std::string> rLzwDecoderDictEntry;

class rLzwDecoder : public rLzwBase{
public:
	rLzwDecoder();
	
	int Decode(rBitStreamIn& in, std::ostream& out);
private:
	void InitDict();
	void AddDictionaryEntry(const std::string& str);
	void WriteCodeOut(unsigned int code, std::ostream& out);
	
private:
	
	rLzwDecoderDict m_dictionary;	
};

#endif
