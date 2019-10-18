#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int division(int,int);	//prototype

int main (void)		//main function
{
int i, divisor, quotient;	//initialize variables
int count=0;

srand ((int) time(NULL));	//initialize random generator

for (i=0; i<10; i++)	//loop to generate the 10 tests
{
	divisor = rand () % 12+1;	//random numbers between 1 and 12
	quotient = rand() % 13;		//random numbers between 0 and 12
	printf("What is %d/%d?\n", divisor*quotient, divisor);	//show the problem and create the dividend
	if (division (divisor, quotient)==0)	//if return value is 0 wrong
	{
		printf("Incorrect, the answer is %d\n", quotient);
	}else{
		printf("Correct!\n");
		count++;	//use to show the number correct total
	}
}

printf("You got %d correct out of 10\n", count);

return 0;
}


int division (int divisor, int quotient)	//function for user input and compare to actual answer
{
int user;
	
scanf("%d",&user);	//user input
if (user==quotient)	//check if correct or not
	return 1;
else
	return 0;
}
	
