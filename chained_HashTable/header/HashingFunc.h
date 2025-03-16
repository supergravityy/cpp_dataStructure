#pragma once

#include "Libs.h"

#define UNSIGNED_WORD_MSB   (0xf0000000)
#define MULTI_CONSTANT      (0.618)

class HashingFunc
{
public:
    HashingFunc(){}
    ~HashingFunc(){}

    // manage
    int HashingFunc_Modulation(const int* Key);
    int HashingFunc_Multiplication(const int* Key);
    int HashingFunc_String(char* Key);

    // utility
    int HashingFunc_getTableSize();
    bool HashingFunc_setTableSize(int size);

protected:
    int tableSize;

private:
    bool HashingFunc_isPrime(int num);
};
