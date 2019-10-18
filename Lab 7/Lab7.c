#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NODE struct node	//define node for global use

struct node	//define node
{
	char listnames[20];   
	int listsize;
	NODE *next;		//node pointer to next
};

NODE *head[4];	//global variables type node array (head and tail)
NODE *tail[4];

void schedule(char *, int b, int);	//prototype structures
void opening();
void list();
void save_data(char *);
void read_file(char *);
int checknames();
int toswitch();

int main(int argc, char *argv[])	//arg are from file
{
int user;
char namecheck[20];
int tempsize = 0;
int i;			//use to travel the array of nodes
NODE *p;		//use to free nodes after use
NODE *q;


if (argc == 1)	//Check to see if put name of file or not
{
	printf("The name of the file is missing!\n");
	return 1;
}
else
	read_file(argv[1]);	//do read function

while (1)
{
        printf("Press (1) to add a party.\nPress (2) to remove a party.\nPress (3) to list all parties.\nPress (4) to quit\n");

        scanf("%d", &user);     //user input
                switch (user)           //start switch (takes place of if-else statement)
                {
                case 1:
			printf("Please input your name and the number of people in your party\n");
			printf("Name: ");
			scanf("%s", namecheck);         //use to check for repetition
			printf("Party number: ");
			scanf("%d", &tempsize); 
			if (checknames(namecheck, tempsize) == 1)	//use function to check
				break;
                        else 
				schedule(namecheck, tempsize, toswitch(tempsize));	//function schedule with the value from toswitch function
                        break;

                case 2:
                        opening();
                        break;

                case 3:
                        list();
                        break;

		default:
                        save_data(argv[1]);	//save when quitting
			for (i=0; i<4; i++)	//travel array to free nodes
			{
				p = q = head[i];
				while (p != NULL)
				{
					q = p;
					p = p->next;
					free(q);
				}
				head[i] = NULL;
				tail[i] = NULL;
			}
			return 0;
                }
}
}


int checknames(char i[], int o)		//check arguments
{
NODE *q;
NODE *p;
int j;

for (j=0; j<4; j++)	//go through array of nodes
{
	p = head[j];       //start p at head to taverse nodes starting at head[[0]

	while (p != NULL)       //goes through nodes to check for repetition
	{
        	if (strcmp(p->listnames,i) == 0)
        	{
                	printf("That name is already in use, please use another.\n");
                	return 1;
        	}
        	p = p->next;    //this is what moves the node
	}
}
return 0;
}

int toswitch(b)		//use this to decide which group to put the nodes into
{
	switch (b)
	{
	case 0:
		printf("No table size input\n");	//if no size, return nothing
		return -1;
		break;
	case 1:
	case 2:
		return 0;		//if size 1 or 2 return 0
		break;
	case 3:
	case 4:
		return 1;		//if size 3 or 4 return 1
		break;
	case 5:
	case 6:
		return 2;		//if size 5 or 6 return 2
		break;
	default:
		return 3;		// if size 7 or higher return 3
		break;
	}
}
	

void schedule(char a[], int b, int c)		//recieve the name, size and which group the size fits in as an argument
{
NODE *q;		//pointers type node
NODE *p;

q = (NODE*)malloc(sizeof(NODE));	//allocate memory
if (q == NULL)		//check if allocation posible
{
	printf("No memory to be allocated.");
	return;
}

if (head[c] == NULL)	//set head and tail to same location if no nodes at that certain group in array
{
	head[c] = q;
	tail[c] = head[c];
}

p = head[c];	//start p at head to taverse nodes

tail[c]->next = q;
strcpy(q->listnames,a);		//copy name over after check
q->listsize = b;		//copy size over after name checks out
q->next = NULL;		//set q of next to NULL
tail[c] = q;
return;
}


void opening(void)
{
int temp = 0;
NODE *p;
NODE *q;
int i;

if (head == NULL)	//check if there is anything inputted
{
        printf("There are no reservtions.\n");
	return;
}
else
{
	printf("Please input the table size that opened up.\n");
        scanf("%d", &temp);	//temporary variable for what you want to get rid of
	for (i=toswitch(temp); i>-1; i--)	//travel array starting at the size of the user input and then go down looking for parties that fit
	{
		p = head[i];
		q = p;
		while (p != NULL)	//sets the bounds of the loop
		{
			if (p->listsize <= temp)	//traverse nodes to find first table that fits
                	{
                       		if (p->next == NULL && p == head[i])	//1 element only
				{
					printf("Table size of %d has opened up\n", p->listsize);
					head[i] = tail[i] = NULL;
					free (p);
					return;
				}
				else if (p->next == NULL)	//last element in list
				{
					printf("Table size of %d has opened up\n", p->listsize);
					tail[i] = q;
					q->next = NULL;
					free (p);
					return;
				}
				else if (p == head[i])	//first element in list
				{
					printf("Table size of %d has opened up\n", p->listsize);
					head[i] = p->next;
					free (p);
					return;
				}
				else if (p->next != NULL)	//middle of the list
				{
					printf("Table size of %d has opened up\n", p->listsize);
					q->next = p->next;
					free (p);
					return;
				}
			}
			q = p;		//q chases p
			p = p->next;	//p traverses node
        	}
	}
        if (p == NULL)
        {
                printf("Table size not found\n");	//p reaches end if = NULL
	}
}
}
        
void list(void)
{
NODE *p;	//to traverse nodes
int i;

printf("Group 1 has table sizes 1 and 2\nGroup 2 has table sizes 3 and 4\nGroup 3 has table sizes 5 and 6\nGroup 4 has table sizes 7 and up.\n");	//label the sizes that correlate to each group

for (i=0; i<4; i++)	//travel array of nodes
{
p = head[i];

if (p != NULL)
{
	printf("\nThe schedule for group %d is as follows:\n", i+1);	//displays all names and listsize
	while (p != NULL)
	{
		printf("%s party of %d\n", p->listnames, p->listsize);
		p = p->next;
	}
}
else
	printf("\nNo reservations scheduled for group %d.\n", i+1);
}
return;
}

void read_file(char *x)
{
FILE *fp;
char name[20];
int number;

fp = fopen(x, "r");
if (fp == NULL)		//alwasy check
{
	printf("File is empty.\n");
	return;
}

fseek(fp, 46, SEEK_SET);	//check after the length of header

while (fscanf(fp, "%s\t%d", name, &number) > 1)		//read through and then insert with what is found after header in file
	schedule(name, number, toswitch(number));

fclose (fp);
return;
}

void save_data(char *x)	//function to save when quit
{
FILE *fp;	//file pointer
NODE *p;
char header[] = "Name\tGroup Size\n-----------------------------\n";		//this is header given
int i;

fp = fopen(x, "w");
if (fp == NULL)		//always check
{
	printf("Unable to save data.\n");
	return;
}

fprintf(fp, "%s", header);	//copy over header

for (i=0; i<4; i++)	//make sure to travel each group in the array
{
	p = head[i];
	while (p != NULL && fprintf(fp, "%s\t%d\n", p->listnames, p->listsize) > 0)	//check to end of nodes and makes sure to copy if there
		p = p->next;
	
}
fclose (fp);
return;
}
