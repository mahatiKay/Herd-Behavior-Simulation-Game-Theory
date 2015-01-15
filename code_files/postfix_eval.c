#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "in_postfix.h"
#define MAX 100

struct stacks
{
	int a[MAX];
	int top;
}sts;

int isemptys()
{
	if(sts.top==-1)return 1;
	return 0;
}

int isfulls()
{
	if(sts.top==MAX)return 1;
	return 0;
}

void pushs(int c)
{
	if(isfulls())printf("\nStack overflow!!");
	else
	{
		sts.top++;
		sts.a[sts.top]=c;;
	}
}

int pops()
{
	if(isemptys())printf("\nStack is empty.");
	else
	{
		sts.top--;
	}
	return sts.a[sts.top+1];
}

void displays()
{
	int i;
		//for(i=sts.top;i>=0;i--)
			printf("\n%d",sts.a[sts.top]);
	//return sts.a[sts.top];
}

int main()
{
    int i=0,k=0;
    int x;
    sts.top=-1;
    char* iexp;
	iexp = (char*)malloc(100*sizeof(char));
	iexp=in_postfix();
    for(i=1;iexp[i]!='\0';i++)
    {
         if((iexp[i]>='0')&&(iexp[i]<='9'))    
         {
             x=0;
             while(iexp[i]!=',')
             {
				 
					 x+=iexp[i]-48;
					 i++;
					 if(iexp[i]!=',')x*=10;

			}
             pushs(x);
         }
		
         else if(iexp[i]=='^')
         {
			 x=pops();
			 x=pow(pops(),x);
			 pushs(x);
         }
		else if(iexp[i] == 'x')
		{
			x = 5;
			pushs(x);
		}
         else if(iexp[i]=='+')
         {
              x=pops();
              x=x+pops();
              pushs(x);
         }
         else if(iexp[i]=='-')
         {
              x=pops();
              x=x-pops();
              pushs(x);
         }        
         else if(iexp[i]=='*')
         {
              x=pops();
              x=x*pops();
              pushs(x);
         }
         else if(iexp[i]=='/')
         {
              x=pops();
              x=x/pops();
              pushs(x);
         }        
         else continue;
    }
    displays();
    return 0;
}     
