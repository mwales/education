#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// copied from stack-overflow 
// https://stackoverflow.com/questions/53056369/c-infinite-loop-when-char-input-instead-of-int
void empty_stdin (void) /* simple helper-function to empty stdin */
{
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}


void deobfuscate(char* str)
{
	while(*str != 0)
	{
		if ( (*str >= 'A') && (*str <= 'Z') )
		{
			// it's uppercase
			if (*str < 'N')
			{
				*str += 13;
			}
			else
			{
				*str -= 13;
			}
		}
		else if ( (*str >= 'a') && (*str <= 'z') )
		{
			// lowercase
			if (*str < 'n')
			{
				*str += 13;
			}
			else
			{
				*str -= 13;
			}
		}
		
		// all other characters, do nothing
		str++;
	}
}

void playGame()
{
	int value = random() % 1000;

	int guess = -1;
	while (guess != value)
	{
		printf("Guess a number\n");
		scanf("%d", &guess);
		empty_stdin();

		printf("You guessed %d.  ", guess);

		if (guess < value)
		{
			printf("Too low!\n");
		}
		else if (guess > value)
		{
			printf("Too high.\n");
		}
		else
		{
			printf("Great job\n");
		}
	}
}

#define GUESS_LEN 255

bool playQuiz()
{
	printf("You must answer some security questions before getting the flag\n");

	printf("What is my favorite video game?\n");
	char guess[GUESS_LEN];
	memset(guess, 0, GUESS_LEN);

	scanf("%250s", guess);
	empty_stdin();

	printf("You guessed %s.  ", guess);
	
	if (strcmp(guess, "uncharted_2") != 0)
	{
		printf("WRONG - intruder!\n");
		return false;
	}
	
	printf("Correct.\n");
	
	printf("Favorite car?\n");
	memset(guess, 0, GUESS_LEN);
	
	scanf("%200s", guess);
	empty_stdin();
	
	printf("You guessed %s. ", guess);
	if ( (strcmp(guess, "toyota_supra") == 0) )
	{
		printf("Ho Ho NO  Too SLOW!!!\n");
		return false;
	}
	
	if ( (strcmp(guess, "1969_camaro_z28") != 0) )
	{
		printf("Nice try, but nope.\n");
		return false;
	}
	
	return true;
}



int main(int argc, char** argv)
{
	// Initialize the random number generator
	srandom(time(0));

	playGame();

	printf("Exitting\n");

	if (playQuiz())
	{
		printf("Quiz success\n");
	}
	else
	{
		printf("LOL.  Nice try hacker!\n");
		return 0;
	}
	
	char flag[GUESS_LEN];
	strncpy(flag, "REPLACE_ME_WITH_FLAG_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", GUESS_LEN);
	deobfuscate(flag);
	
	printf("%s\n", flag);

	return 0;
}

