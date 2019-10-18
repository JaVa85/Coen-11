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

NODE *head = NULL;	//global variables type node (head and tail)
NODE *tail = NULL;

void schedule(char *, int b);	//prototype structures
void opening();
void list();
void save_data(char *);
void read_file(char *);
int checknames();

int main(int argc, char *argv[])	//arg are from file
{
int user;
char namecheck[20];
int tempsize = 0;

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
				schedule(namecheck, tempsize);
                        break;

                case 2:
                        opening();
                        break;

                case 3:
                        list();
                        break;

		default:
                        save_data(argv[1]);	//save when quitting
			return 0;
                }
}
}


int checknames(char i[], int o)		//check arguments
{
NODE *q;
NODE *p;

p = head;       //start p at head to taverse nodes

while (p != NULL)       //goes through nodes to check for repetition
{
        if (strcmp(p->listnames,i) == 0)
        {
                printf("That name is already in use, please use another.\n");
                return 1;
        }
        p = p->next;    //this is what moves the node
}
return 0;
}


void schedule(char a[], int b)
{
NODE *q;		//pointers type node
NODE *p;

q = (NODE*)malloc(sizeof(NODE));	//allocate memory
if (q == NULL)		//check if allocation posible
{
	printf("No memory to be allocated.");
	return;
}

if (head == NULL)	//set head and tail to same location if no nodes
{
	head = q;
	tail = head;
}

p = head;	//start p at head to taverse nodes

tail->next = q;
strcpy(q->listnames,a);		//copy name over after check
q->listsize = b;		//copy size over after name checks out
q->next = NULL;		//set q of next to NULL
tail = q;
return;
}


void opening(void)
{
int temp = 0;
NODE *p;
NODE *q;

if (head == NULL)	//check if there is anything inputted
{
        printf("There are no reservtions.\n");
	return;
}
else
{
        p = head;	//start p at head to chase
	q = p;
	printf("Please input the table size that opened up.\n");
        scanf("%d", &temp);	//temporary variable for what you want to get rid of
	while (p != NULL)	//sets the bounds of the loop
	{
		if (p->listsize <= temp)	//traverse nodes to find first table that fits
                {
                       if (p->next == NULL && p == head)	//1 element only
			{
				head = tail = NULL;
				free (p);
				return;
			}
			else if (p->next == NULL)	//last element in list
			{
				tail = q;
				q->next = NULL;
				free (p);
				return;
			}
			else if (p == head)	//first element in list
			{
				head = p->next;
				free (p);
				return;
			}
			else if (p->next != NULL)	//middle of the list
			{
				q->next = p->next;
				free (p);
				return;
			}
		}
		q = p;		//q chases p
		p = p->next;	//p traverses node
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
p = head;

if (head == NULL)
{
        printf("No reservations scheduled.\n");
	return;
}
else
{
	printf("The schedule for the day is as follows:\n");	//displays all names and listsize
	while (p != NULL)
	{
		printf("%s party of %d\n", p->listnames, p->listsize);
		p = p->next;
	}
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
	schedule(name, number);

fclose (fp);
return;
}

void save_data(char *x)	//function to save when quit
{
FILE *fp;	//file pointer
NODE *p;
char header[] = "Name\tGroup Size\n-----------------------------\n";		//this is header given

fp = fopen(x, "w");
if (fp == NULL)		//always check
{
	printf("Unable to save data.\n");
	return;
}

fprintf(fp, "%s", header);	//copy over header

p = head;
while (p != NULL && fprintf(fp, "%s\t%d\n", p->listnames, p->listsize) > 0)	//check to end of nodes and makes sure to copy if there
	p = p->next;
fclose (fp);
return;
}
