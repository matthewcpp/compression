#include "rLzwBase.hpp"

void rLzwBase::IncrementNextCodeId(){
	m_nextCodeId += 1;
	if (m_nextCodeId >= IntPow(2 , m_codeSize))
		m_codeSize += 1;
}

int rLzwBase::IntPow(int base, unsigned int exp){
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

