#include <stdio.h>
#include <string.h>
#define SIZE 10

char listnames[SIZE][SIZE];	//global variables
int listsize[SIZE];
int counter = 0;

void schedule();
void opening();
void list();

int main(void)
{
int i;
int user;

for (i=0; i<SIZE; i++)
{
	listnames[i][0]='\0';
}

for (;;)
{
	printf("Press (1) to add a party\nPress (2) to remove a party\nPress (3) to list all parties\nPress (4) to quit\n");

	scanf("%d", &user);	//user input
		switch (user)		//start switch (takes place of if-else statement
		{
		case 1:

			schedule();
			break;
		
		case 2:
			opening();
			break;
		
		case 3:
			list();
			break;
		
		default:
			return 0;
		}
}
}


void schedule(void)
{
char namecheck[SIZE];
int i,j;

if (counter==SIZE)	//make sure list isn't full
{
	printf("Waiting list is full\n");
}
else
{
	printf("Please input your name\n");
	scanf("%s", namecheck);			//check for duplicate
	for (i=0; i<SIZE; i++)
	{
		if (strcmp(namecheck,listnames[i])==0)
		{
			printf("That name is already in use, please use another\n");
			break;
		}
	}
	if (strcmp(namecheck,listnames[i])!=0)
		for (j=0; j<strlen(namecheck); j++)
		{
			strcpy(listnames[counter],namecheck);
			printf("Please input the number of people in your party\n");
			scanf("%d", &listsize[counter]);
			counter++;
			break;
		}
}
return;
}


void opening(void)
{
int i,j;
int temp=0;
int max = 0;
int loc=0;

if (counter==0)
{
	printf("There are no reservtions.\n");
}
else
{
	printf("Please input the table size that opened up.\n");
	scanf("%d", &temp);
	for (i=0; i<SIZE; i++)
	{
		if (listsize[i]<=temp && listsize[i]>max)
		{	
			max=listsize[i];
			loc=i;
		}
	}
	if (max!=0)
	{
		printf("%s party of %d was seated.\n", listnames[loc], listsize[loc]);
		for (j=loc; j<SIZE-1; j++)
		{
			strcpy(listnames[j],listnames[j+1]);
			listsize[j] = listsize[j+1];
		}
		counter--;
	} 
	else
	{ 
		printf("no parties could fit that table size");
	}
}
return;
}


void list(void)
{
int i;

if (counter==0)
{
	printf("No reservations scheduled.\n");
}
else
{
	for (i=0; i<SIZE; i++)
	{
		if (listnames[i][0]!='\0')
		{	
			printf("%s party of %d\n",listnames[i],listsize[i]);
		}
	}
}
return;
}







