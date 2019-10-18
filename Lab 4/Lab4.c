#include <stdio.h>
#include <string.h>
#define SIZE 10

void input();	//prototype
void delete();
void list();

typedef union	//create union
{
	char sname[2*SIZE];
	float salary;
	int retire;
} STATUS;	//name

struct stuff	//create structure
{
	char name[2*SIZE];
	int age;
	STATUS status;		//initialize in struct
};

struct stuff x[SIZE];	//initialize structure
int counter = 0;


int main(void)
{
int user;

for (;;)
{
	printf("Press (1) to input a person\nPress (2) to delete a person\nPress (3) to list people in the system\nPress (4) to quit\n");

	scanf("%d", &user);	
		switch (user)	//switch statement between three functions
		{
			case 1:
				input();
				break;
			case 2:
				delete();
				break;
			case 3:
				list();
				break;
			default:
				return 0;
		}
}
}


void input(void)
{
char tempname[20];
int i;

printf("Please input your name\n");
scanf("%s", tempname);		//input name into structure
	for (i=0; i<counter; i++)
	{
		if (strcmp(x[i].name,tempname)==0)
		{
			printf("That name is already in use, please use another\n");
			return;
		}
	}
strcpy(x[counter].name,tempname);
printf("Please input your age\n");
scanf("%d", &x[counter].age);		//input age into structure
if (x[counter].age <= 21)		//checks the age to determine what to use from union
{
	printf("Please input your school name\n");
	scanf("%s", x[counter].status.sname);	//put school name into union
	counter++;
} else if (x[counter].age > 21 && x[counter].age < 65)		//next age check
{
	printf("Please input your salary per month\n");
	scanf("%f", &x[counter].status.salary);		//put salary into union
	counter++;
}
else
{
	printf("Please input the year of your retirement\n");	
	scanf("%d", &x[counter].status.retire);		//puts retirement year into union
	counter++;
}
return;
}


void delete(void)
{
char tempname[SIZE];
int i;

printf("Please input the name you wish to remove\n");
scanf("%s", tempname);

if (counter==0)		//make sure someone is in the system
{
	printf("There is nobody in the system\n");	
	return;
}
else
{
	for (i=0; i<counter; i++)	//go through the structure
	{
		if (strcmp(x[i].name,tempname)==0)	//compare the input name with names in the system
		{
			printf("%s has been removed from the list\n", x[i].name);
			x[i]=x[counter-1];	//replace the element with the lowest element
			counter--;	//remember to lower the counter
			break;
		}
	}
}
return;
}


void list(void)
{
int i;

if (counter==0)		//checks to see if someone is even in the system
{
	printf("There is currently no one in the system");
	return;
}
for (i=0; i<counter; i++)	//goes through the entire structure
{
	printf("Name: %s Age: %d", x[i].name, x[i].age);	//prints the name and age found in struct
	if (x[i].age <= 21)	//checks the age to determine what to print from the union
		printf(" School Name: %s\n", x[i].status.sname);
	else if (x[i].age > 21 && x[i].age < 65)
		printf(" Salary per Month: %.2f\n", x[i].status.salary);
	else
		printf(" Year of Retirement: %d\n",  x[i].status.retire);
}
return;
}
