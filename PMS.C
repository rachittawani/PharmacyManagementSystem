#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define size 5
int count=0;

struct node
{
	struct node *next;
	int age,pno,nm;
	char name[20],contact[20],email[20];
	struct medicine
	{
		char med[20];
		int price;
		int quant;

	}m[20];

}*temp=NULL,*temp1=NULL,*m=NULL;
struct node *chain[size];
struct node* create();
void line_hor(int column1, int column2, int row, char c)
{
	for(column1;column1<=column2;column1++)
	{
		gotoxy(column1,row);
		printf("%c",c);
	}
	printf("\n");
}
void line_ver(int row1, int row2, int column, char c)
{
	for(row1;row1<=row2;row1++)
	{
		gotoxy(column,row1);
		printf("%c",c);
	}
}
void box(int column1, int row1, int column2, int row2, char c)
{
	char ch=218;
	char c1,c2,c3,c4;
	char l1=196,l2=179;
	if (c==ch)
	{
		c1=218;
		c2=191;
		c3=192;
		c4=217;
		l1=196;
		l2=179;
	}
	else
	{
		c1=c;
		c2=c;
		c3=c;
		c4=c;
		l1=c;
		l2=c;
	}
	gotoxy(column1,row1) ;
	printf("%c",c1);
	gotoxy(column2,row1) ;
	printf("%c",c2);
	gotoxy(column1,row2) ;
	printf("%c",c3);
	gotoxy(column2,row2) ;
	printf("%c",c4);
	column1++ ;
	column2-- ;
	line_hor(column1,column2,row1,l1) ;
	line_hor(column1,column2,row2,l1) ;
	column1-- ;
	column2++ ;
	row1++ ;
	row2-- ;
	line_ver(row1,row2,column1,l2) ;
	line_ver(row1,row2,column2,l2) ;
}
void login()
{
	int lm;
	clrscr();
	label:gotoxy(38,5);
	printf("LOGIN");
	box (30,6,50,9,218);
	gotoxy(31,7);
	printf("Enter password:");
	scanf("%d",&lm);
	if(lm==235)
	{
		gotoxy(35,8);
		printf("  Welcome ");
		delay(1000);
	}
	else
	{
		gotoxy(35,8);
		printf("Try again");
		goto label;
	}
}
struct node* search()
{
	int value,key;
	printf("Enter the pharmacy number:");
	scanf("%d",&value);
	key=value%size;
	temp=chain[key];
	while(temp)
	{
		if(temp->pno==value)
		{
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
}
void init()
{
	int i;
	for(i=0;i<size;i++)
		chain[i]=NULL;
}
void reg()
{
	int key,value;
	m=malloc(sizeof(struct node));
	printf("Enter the Pharmacy Number:");
	scanf("%d",&value);
	m=create(value);
	key=value%size;

	if(chain[key]==NULL)
		chain[key]=m;
	else
	{
		temp1=chain[key];
		while(temp1->next)
		{
			temp1=temp1->next;
		}
		temp1->next=m;
	}
	return;
}
struct node *create(int value)
{
	int i;
	temp=(struct node*)malloc(sizeof(struct node));
	printf("Enter the person detail:\n");
	temp->pno=value;
	printf("Name:");scanf("%s",temp->name);flushall();
	printf("Age:");scanf("%d",&temp->age);
	printf("Contact Number:");scanf("%s",temp->contact);flushall();
	printf("Email:");scanf("%s",temp->email);flushall();
	printf("Enter the number of medicine:");
	scanf("%d",&temp->nm);
	for(i=0;i<temp->nm;i++)
	{
		printf("Medicine Name:");scanf("%s",temp->m[i].med);flushall();
		printf("Enter price of one tablet:");scanf("%d",&temp->m[i].price);
		printf("Number of tablets:");scanf("%d",&temp->m[i].quant);
	}
	temp->next=NULL;
	count++;
	return temp;

}
void display()
{
	int i,j;
	printf("P NO.\tNAME\tAGE\tCONTACT NO.\tEMAIL");
	for(i=0;i<size;i++)
	{
		temp=chain[i];
		while(temp)
		{
			printf("\n%d\t%s\t%d\t%s\t%s",temp->pno,temp->name,temp->age,temp->contact,temp->email);
			for(j=0;j<temp->nm;j++)
			{
				printf("\nMED:%s\tQUANTITY=%d",temp->m[j].med,temp->m[j].quant);
			}
			temp=temp->next;
		}
		printf("\n");

	}
}
void Delete()
{
	int flag=0,value,key;
	printf("Enter the pharmacy number of person to be deleted:");
	scanf("%d",&value);
	key=value%size;
	temp=chain[key];
	if(!temp)
	{
		printf("Not found");
		return;
	}
	temp1=temp;
	while(temp!=NULL)
	{
		if(temp->pno==value)
		{
			flag=1;
			if(temp==chain[key])
				chain[key]=temp->next;
			else
				temp1->next=temp->next;
			count--;
			free(temp);
			break;
		}
		temp1=temp;
		temp=temp->next;
	}
	if(flag)
		printf("DELETED");
	else
		printf("Not found");
	return;
}
void bill()
{
	int i,sum=0,x=0;
	temp=(struct node*)malloc(sizeof(struct node));
	temp=search();
	if(temp)
	{
		box(8,3,73,20,218);
		gotoxy(10,4);
		printf("Serial Number");
		gotoxy(28,4);
		printf("Medicine");
		gotoxy(48,4);
		printf("Quantity");
		gotoxy(68,4);
		printf("Price");
		for(i=0;i<temp->nm;i++)
		{
			gotoxy(12,i+5);
			printf("%d",i+1);
			gotoxy(30,i+5);
			printf("%s",temp->m[i].med);
			gotoxy(50,i+5);
			printf("%d",temp->m[i].quant);
			gotoxy(70,i+5);
			x=(temp->m[i].price)*(temp->m[i].quant);
			printf("%d",x);
			sum=sum+x;
		}
		gotoxy(57,17);
		printf("Total bill=");
		gotoxy(70,17);
		printf("%d",sum);
	}
	else
		printf("Person not found");
}

void logout()
{
	gotoxy(32,10);
	printf("LOGOUT SUCCESSFULLY");
	delay(3000);
	exit(0);
}
void edit()
{
	int choice;
	m=(struct node*)malloc(sizeof(struct node));
	m=search();
	if(m!=NULL)
	{
		printf("Found\n");
		printf("1.Name\n2.Age\n3.Contact\n4.Email\n5.Finish editing\n");
		while(1)
		{
			printf("Enter the detail to be edited\n");
			scanf("%d",&choice);
			if(choice==1)
			{
				printf("Enter the new name: ");
				scanf("%s",m->name);
			}
			else if(choice==2)
			{
				printf("Enter the new age: ");
				scanf("%d",&m->age);
			}
			else if(choice==3)
			{
			       printf("Enter the new contact: ");
			       scanf("%s",m->contact);
			}
			else if(choice==4)
			{
				printf("Enter the new email: ");
				scanf("%s",m->email) ;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		printf("Not found");
		delay(3000);
	}
}
void update()
{
	int choice;
	temp=(struct node*)malloc(sizeof(struct node));
	temp=search();
	if(temp)
	{
		printf("1.Add new medicine\n2.Finish update\n");
		while(1)
		{
			printf("Enter your choice:");
			scanf("%d",&choice);
			if(choice==1)
			{
				printf("Medicine Name:");scanf("%s",temp->m[temp->nm].med);flushall();
				printf("Enter price of one tablet:");scanf("%d",&temp->m[temp->nm].price);
				printf("Number of tablets:");scanf("%d",&temp->m[temp->nm++].quant);
			}
			if(choice==2)
			{
				break;
			}
		}
	}
	else
	{
		printf("Not found\n");
		delay(3000);
	}
}
void menu()
{
	int valid;
	int n=8;
	int x=18;
	char ch1,ch2;
	char chr1=219,chr=175;
	clrscr();
	do
	{
		box(1,2,80,24,219);
		line_hor(9,72,6,196);
		box(8,3,73,20,218);
		gotoxy(25,23);
		printf("%c",24);
		printf("%c",25);
		printf("=Move <ENTER>=Select <ESC>=Exit");
		gotoxy(13,5);
		printf("%c",chr1);
		textbackground(WHITE);
		textcolor(BLACK);
		gotoxy(14,5);
		cprintf("PHARMACY MANAGEMENT SYSTEM ");
		textbackground(BLACK);
		textcolor(LIGHTGRAY);
		gotoxy(14,8);
		printf("MENU");
		gotoxy(14,9);
		printf("-----");
		gotoxy(14,11);
		printf("REGISTER");
		gotoxy(14,12);
		printf("EDIT");
		gotoxy(14,13);
		printf("UPDATE");
		gotoxy(14,14);
		printf("BILL");
		gotoxy(14,15);
		printf("DISPLAY");
		gotoxy(14,16);
		printf("DELETE");
		gotoxy(14,17);
		printf("SEARCH");
		gotoxy(14,18);
		printf("LOGOUT");
		gotoxy(12,x);
		printf("%c",chr);
		gotoxy(13,5);
		do
		{
			do
			{
				do
				{
					ch1=getch();
					if(ch1==27)
					{
						textmode(C80);
						clrscr();
						exit(0);
					}
				}while((ch1!=0)&&(ch1!=13));
				if(ch1!=13)
				{
					do
					{
						ch2=getch();
						if(ch2==27)
						{
							textmode(C80);
							clrscr();
							exit(0);
						}
					}while((ch2!=72)&&(ch2!=80)&&(ch2!=13));
				}
			}while(((ch1!=0)||((ch2!=72)&&(ch2!=80)))&&((ch1!=13)&&(ch2!=13)));
			if((ch1==0)&&(ch2==80))
			{
				gotoxy(12,x);
				printf(" ");
				if(n==8)
				{
					n=1;
					x=x-7;
				}
				else
				{
					n=n+1;
					x=x+1;
				}
				gotoxy(12,x);
				printf("%c",chr);
				gotoxy(13,5);
				sound(200);
				delay(30);
				nosound();
			}
			if((ch1==0)&&(ch2==72))
			{
				gotoxy(12,x);
				printf(" ");
				if(n==1)
				{
					n=8;
					x=x+7;
				}
				else
				{
					n=n-1;
					x=x-1;
				}
				gotoxy(12,x);
				printf("%c",chr);
				gotoxy(13,5);
				sound(200);
				delay(30);
				nosound();
			}
		}while((ch1!=13)&&(ch2!=13));
		if(n==1)
		{
			char t,r;
			clrscr();
			do
			{
				reg();
				printf("To register another person press y or else n:");
				scanf("%c%c",&t,&r);
			}while(r=='Y'||r=='y');
			clrscr();
		}
		if(n==2)
		{
			clrscr();
			edit();
			clrscr();
		}
		if(n==3)
		{

			clrscr();
			update();
			clrscr();

		}
		if(n==4)
		{
			clrscr();
			bill();
			delay(3000);
			clrscr();
		}


		if(n==5)
		{
			clrscr();
			display();
			delay(5000);
			clrscr();
		}
		if(n==6)
		{
			clrscr();
			Delete();
			delay(3000);
			clrscr();
		}
		if(n==7)
		{
			clrscr();
			temp=search();
			if(temp==NULL)
				printf("Not found");
			else
				printf("Found");
			delay(3000);
			clrscr();

		}
		if(n==8)
		{
			clrscr();
			logout();
		}
	}while(n!=8);
	textmode(C80) ;
	clrscr() ;
}

void main()
{
	clrscr();
	init();
	login();
	menu();
	getch();
}