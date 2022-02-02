#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
   if (argc < 2)
   {
      printf("Usage: %s number\n", argv[0]);
      return 1;
   }

   int solution = 1;
   for(int i = atoi(argv[1]); i; i--)
   {
      solution *= i;
   }
   printf("%s! = %d\n", argv[1], solution);

   return 0;
}	
