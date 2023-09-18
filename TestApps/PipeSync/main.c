// This application will fork itself and have a bunch of processes synced using a pipe

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		printf("Usage: %s delay1 [delay2 ... ]\n", argv[0]);
		return 0;
	}
	
	pid_t parentPid = getpid();
	printf("Parent PID = %d\n", parentPid);

	int pipeFds[2];
	int status = pipe(pipeFds);
	if (status)
	{
		printf("Error creating pipe\n");
		return 0;
	}

	int numProcs;
	for(numProcs = 1; numProcs < argc; numProcs++)
	{
		pid_t childPid = fork();

		if (childPid == 0)
		{
			// This is a child process
			break;
		}

	}
	
	int afterForkPid = getpid();

	if(afterForkPid != parentPid)
	{
		// We are a child
		for(int i = 0; i < atoi(argv[numProcs]); i++)
		{
			printf("Child pid %d delaying for %d seconds\n", afterForkPid, i);
			sleep(1);
		}

		// Closing all pipes
		close(pipeFds[0]);
		close(pipeFds[1]);
	}
	else
	{
		// This is the parent pid, going to wait for all the children to start and get to sync point
		close(pipeFds[1]); // close write end of pipe

		char buf[0x10];
		int br = read(pipeFds[0], buf, 0x10);
		printf("Parent pid read %d pipes from pipe\n", br);
		printf("Parent bytes read should be an error after all the delays have completed and exitted\n");
		close(pipeFds[0]);
	}

		
	printf("Pid %d exitting\n", getpid());

	return 0;

}

