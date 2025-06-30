#include "../header/HashFunc.h"

int defaultFunc::method_Division(const void* key, int bucketCnt)
{
	int myKey = *(int*)key;

	return myKey % bucketCnt;
}

int defaultFunc::method_multiplication(const void* key, int bucketCnt) // for string hashFunction
{
	const char* ptr = (const char*)key;
	int value = 0;

	while (*ptr != '\0')
	{
		int tmp;
		
		value = (value << 4) + (*ptr);

		if (tmp = (value & 0xf0000000))
		{
			value ^= (tmp >> 24);
			value ^= tmp;
		}
		ptr++;
	}

	return value % bucketCnt;
}