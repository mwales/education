#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <set>
#include <fstream>
#include <algorithm>
#include <assert.h>

#include "../customstuff.h"

#ifdef AOC_DEBUG
	#define DEBUG std::cout
#else
	#define DEBUG if(0) std::cout
#endif

uint64_t findLoopCount(uint64_t subjectNum, uint64_t modulus, uint64_t keyVal)
{
	uint64_t loops = 1;
	uint64_t keyValCompute = subjectNum;

	while(true)
	{
		keyValCompute *= subjectNum;
		keyValCompute %= modulus;
		loops++;

		if (keyVal == keyValCompute)
		{
			break;
		}
	}

	DEBUG << "loop count = " << loops << std::endl;
	return loops;
}

uint64_t computeKeyVal(uint64_t subjectNum, uint64_t modulus, uint64_t loops, uint64_t startVal)
{
	uint64_t keyValCompute = startVal;

	for(uint64_t i = 0; i < loops; i++)
	{
		keyValCompute *= subjectNum;
		keyValCompute %= modulus;
	}
	
	DEBUG << "Key computed after " << loops << " loops is " << keyValCompute << std::endl;
	return keyValCompute;
}




int main(int argc, char** argv)
{

	if (argc < 2)
	{
		std::cerr << "Provide filename" << std::endl;
		return 0;
	}

	std::vector<std::string> fileData = readFile(argv[1]);

	uint64_t subjectNumber = 7;
	uint64_t modulus = 20201227;

	assert(fileData.size() == 2);

	uint64_t publicKey1 = strtoull(fileData[0].c_str(), NULL, 10);
	uint64_t publicKey2 = strtoull(fileData[1].c_str(), NULL, 10);
	 
	uint64_t loopCount1 = findLoopCount(subjectNumber, modulus, publicKey1);

	DEBUG << "loop count = " << loopCount1 << std::endl;
	
	uint64_t encKey = computeKeyVal(publicKey2, modulus, loopCount1, 1);

	std::cout << "Enc Key = " << encKey << std::endl;
	return 0;
}
