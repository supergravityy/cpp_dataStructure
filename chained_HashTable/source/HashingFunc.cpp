#include "../header/HashingFunc.h"

int HashingFunc::HashingFunc_Modulation(const int* Key)
{
    return  (*Key) % (this->tableSize) ;
}

int HashingFunc::HashingFunc_Multiplication(const int* Key) 
// In this solution, TableSize is not important like modulation
{
    double temp = (double)(*Key) * MULTI_CONSTANT;       // 1. Multiply key by constant A
    double fractionPart = temp - (int)temp;              // 2. Extract fractional part
    int result = (int)(fractionPart * this->tableSize);       // 3. Scale fractional part by bucket size

    return result;                                       
}


int HashingFunc::HashingFunc_String(char* Key)
{
    char *ptr = nullptr;
    int val = 0, temp = 0;

    // 1. change keyVal to intVal by kind of bit operation
    ptr = Key;

    while (*ptr != '\0') 
    // The purpose of this iteration is to mix characters in bits
    {
        val = (val << 4) + (*ptr); // make empty 4bit space

        if (temp = (val & UNSIGNED_WORD_MSB))
        {
            val = val ^ (temp >> 24);
            val = val ^ temp;
        }
        
        ptr++;
    }
    
    return val % this->tableSize; // 2. final modulating operation
}

int HashingFunc::HashingFunc_getTableSize(void)
{
    return this->tableSize;
}

bool HashingFunc::HashingFunc_setTableSize(int size)
{
    if(size <= 0)   return false;
    else if(HashingFunc_isPrime(size) == false) return false;
    else
    {
        this->tableSize = size;
        return true;
    }
}

bool HashingFunc::HashingFunc_isPrime(int num)
{
    if (num <= 1) 
        return false; 

    // check num has divisor by divid from 2 to num-1
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0) 
            return false;
    }

    return true;
}