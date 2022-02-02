#include <stdio.h>

/*
To compile on Linux for 32-bit (you will need gcc-multilib)
 gcc -m32 int_sizes.c -o l32sizes
For Linux 64-bit
 gcc int_sizes.c -o l64sizes

On windows, you have to pick the correct build environment to launch
*/

int main(int argc, char** argv)
{
	int charSize = sizeof(char);
	int sizetSize = sizeof(size_t);
	int shortSize = sizeof(short);
	int intSize = sizeof(int);
	int longSize = sizeof(long);
	int longlongSize = sizeof(long long);
	int floatSize = sizeof(float);
	int doubleSize = sizeof(double);

	printf("charSize = %d\n", charSize);
	printf("sizeTSize = %d\n", sizetSize);
	printf("shortSize = %d\n", shortSize);
	printf("intSize = %d\n", intSize);
	printf("longSize = %d\n", longSize);
	printf("longlongSize = %d\n", longlongSize);
	printf("floatSize = %d\n", floatSize);
	printf("doubleSize = %d\n", doubleSize);

	int ullsize = sizeof(unsigned long long);
	printf("ullSize = %d\n", ullsize);

	return 0;
}

