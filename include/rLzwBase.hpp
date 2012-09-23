#ifndef R_LZWBASE_HPP
#define R_LZWBASE_HPP

class rLzwBase{
protected:
	void IncrementNextCodeId();
	int IntPow(int base, unsigned int exp);
	
protected:
	unsigned int m_codeSize;
	unsigned int m_nextCodeId;
};

#endif
