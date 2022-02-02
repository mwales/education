#include <stdio.h>

int main(int argc, char** argv)
{
	int counter = 10;
	while(counter)
	{
		printf("Counter %d\n", counter);
		counter--;
	}

	return 0;
}	
