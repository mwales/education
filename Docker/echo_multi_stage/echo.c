#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	printf("echo service v0.1\n");

	char buf[0x100];
	int bytesRead;
	while( (bytesRead = read(0, buf, 0xff) ) )
	{
		buf[bytesRead] = 0;
		for(int i = 0; i < bytesRead; i++)
		{
			if ( (buf[i] >= 'a') && (buf[i] <= 'z') )
			{
				buf[i] -= 'a' - 'A';
			}
			else if ( (buf[i] >= 'A') && (buf[i] <= 'Z') )
			{
				buf[i] += 'a' - 'A';
			}
		}

		printf("%s", buf);
	}

	return 0;
}

	   
