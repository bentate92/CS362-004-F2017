#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	//Returns a random ASCII character
	return (rand() % 94) + 32;
}

char *inputString()
{
	//String to be built and returned
	static char string[6];

	//Declare iterator;
	int i;

	//String to hold all unique letters of "reset"
	char rest[5] = "rest";

	//About 1/4 times, it will choose from all characters, and 3/4 of the time, it will only choose from rest string
	if (rand() % 4 == 0) {
		//Choose from all characters
		for (i = 0; i < 5; i++) {
			string[i] = (rand() % 94) + 32;
		}
	} else { 
		//Choose from rest
		for (i = 0; i < 5; i++) {
			//Find index of random letter from "reset"
			int k = rand() % 4;
			
			//Add letter to string
			string[i] = rest[k];
		}
	}

	//Add null-terminator
	string[5] = '\0';

	return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
