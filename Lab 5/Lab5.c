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

void schedule();	//prototype structures
void opening();
void list();

int main(void)
{
int user;

while (1)
{
        printf("Press (1) to add a party.\nPress (2) to remove a party.\nPress (3) to list all parties.\nPress (4) to quit\n");

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

		default:
                        return 0;
                }
}
}


void schedule()
{
char namecheck[20];	//temporary array to check if name already in use
NODE *q;		//pointers type node
NODE *p;
int tempsize = 0;		//helpful for while statement

printf("Please input your name and the number of people in your party\nName: ");
scanf("%s", namecheck);		//use to check for repetition
printf("Party number: ");	
scanf("%d", &tempsize);		//use in conjunction with namecheck

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

while (p != NULL)	//goes through nodes to check for repetition
{
	if (strcmp(p->listnames,namecheck) == 0)
	{
		printf("That name is already in use, please use another.\n");
		return;
	}
	p = p->next;	//this is what moves the node
}

tail->next = q;
strcpy(q->listnames,namecheck);		//copy name over after check
q->listsize = tempsize;		//copy size over after name checks out
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
