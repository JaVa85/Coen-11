#include <stdio.h>
#include <string.h>
#define SIZE 10

struct stuff	//define structure
{
	char listnames[SIZE];   
	int listsize;
};

struct stuff x[SIZE];	//global variables
int counter = 0;

void schedule();	//prototype structures
void opening();
void list();
void match();

int main(void)
{
int user;

for (;;)
{
        printf("Press (1) to add a party\nPress (2) to remove a party\nPress (3) to list all parties\nPress (4) to search for matching party sizes\nPress (5) to quit\n");

        scanf("%d", &user);     //user input
                switch (user)           //start switch (takes place of if-else statement)
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

                case 4:
			match();
			break;

		default:
                        return 0;
                }
}
}


void schedule(void)
{
char namecheck[SIZE];	//temporary array to check if name already in use
struct stuff *p;	//initialize structure pointer
int count=0;		//helpful for while statement

if (counter==SIZE)		//check if list is full
{
	printf("Waiting list is full\n");
	return;
}

printf("Please input your name\n");
scanf("%s", namecheck);
p=x;			//set the pointer equal to the structure
while (count<SIZE)
{
	if (strcmp(namecheck, p->listnames)==0)		//compare the array of names within the structure to user input
	{
		printf("That name is already in use, please use another\n");
		return;
	}
	count++;
	p++;
}
strcpy(x[counter].listnames,namecheck);		//copy the temporary array over to the structure
printf("Please input the number of people in your party\n");
scanf("%d", &x[counter].listsize);	//input party size into structure
counter++;
return;
}


void opening(void)
{
int temp=0;
int max = 0;
int loc=0;
struct stuff *p;
int count=0;

if (counter==0)		//check if list is empty
{
        printf("There are no reservtions.\n");
}
else
{
        printf("Please input the table size that opened up.\n");
        scanf("%d", &temp);	//temporary variable for what you want to get rid of
        p=x;
	while (count<counter)	//sets the bounds of the loop
	{
		if (p->listsize<=temp && p->listsize>max)	//same as previous lab but using pointers instead
                {
                        max=p->listsize;	//update max value for loop
                        loc=count;
                }
		p++;
		count++;
        }
        if (max!=0)
        {
                printf("%s party of %d was seated.\n", x[loc].listnames, x[loc].listsize);
		while (loc<SIZE-1)	//checks after the name being removed
                {
                        strcpy(x[loc].listnames,x[loc+1].listnames);	//moves everything up in the list
                        x[loc].listsize = x[loc+1].listsize;
			loc++;
                }
                counter--;
        }
        else
        {
                printf("no parties could fit that table size\n");
        }
}
return;
}


void list(void)
{
struct stuff *p;
int count=0;

if (counter==0)
{
        printf("No reservations scheduled.\n");
}
else
{
	p=x;
	while (count<counter)
	{
		if (p->listnames!='\0')		//lists everything that is in the structure
		{
			printf("%s party of %d\n",p->listnames,p->listsize);
			p++;
		}
		count++;
	}
}
return;
}

void match(void)
{
struct stuff *p;
int count=0;
int temp=0;
 
if (counter==0)		//checks if structure is empty
{
	printf("No reservations scheduled.\n");
	return;
}

printf("Please input the table size to find a match\n");
scanf("%d", &temp);	//sets input into temp variable
p=x;
while (count<counter)
{
	if (p->listsize==temp)	//if the size is equal to the temp, it will output size
	{
		printf("%s party of %d\n",p->listnames,p->listsize);
	}
	count++;
	p++;
}

return;
}
