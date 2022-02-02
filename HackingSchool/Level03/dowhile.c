#include <stdio.h>

int main(int argc, char** argv)
{
	int counter = 5;

	// A do-while loop will always execute
	// atleast 1 time
	do
	{
		printf("Counter %d\n", counter);
		counter--;
	} while (counter);

	return 0;
}	
