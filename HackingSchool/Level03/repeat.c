#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Incorrect number of params!\n");
		fprintf(stderr, "Usage: repeat word numtimes\n");
		return 1;
	}

	int numtimes = atoi(argv[2]);
	for(int i = 0; i < numtimes; i++)
	{
		puts(argv[1]);
	}
	return 0;
}
