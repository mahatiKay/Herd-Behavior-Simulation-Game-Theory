#include<stdio.h>
#define MAX 100

struct stack
{
	char a[MAX];
	int top;
}st;

int isempty()
{
	if(st.top==-1)return 1;
	return 0;
}

int isfull()
{
	if(st.top==MAX)return 1;
	return 0;
}

void push(char c)
{
	if(isfull())printf("\nStack overflow!!");
	else
	{
		st.top++;
		st.a[st.top]=c;;
	}
}

char pop()
{
	if(isempty())printf("\nStack is empty!!");
	else
	{
		st.top--;
	}
	return st.a[st.top+1];
}

void display()
{
	int i;
	if(isempty())printf("\nEmpty stack");
	else
	{
		printf("\nThe stack is : \n");
		for(i=st.top;i>=0;i--)
			printf("\n%c",st.a[i]);
	}
}

char* in_postfix()
{
    int i=0,k=0;
    char ch;
    st.top=-1;
    char iexp[100];
    char *rexp = (char*)malloc(sizeof(char)*100);
    printf("\nEnter the expression : \n");
    scanf("%s",iexp);
    for(i=0;iexp[i]!='\0';i++)
    {
		switch(iexp[i])
		{
			case '(' : push(iexp[i]);
				break;
			case '^': if(isempty())
			{ 
				
				//printf("\nhee..2");
				push(iexp[i]);
			} 
			else
			{
				ch=pop();
				if(ch=='^')
				{
					rexp[k++] = ',';
					rexp[k]=ch;
					k++;
					
					push(iexp[i]);
				}
				if((ch=='*')||(ch=='/')||(ch=='+')||(ch=='-')||(ch=='('))
				{
					push(ch);
					//printf("\nhee..");
					push(iexp[i]);
				}
			}
				break;
			case '*' : case '/' : if(isempty())push(iexp[i]);
			else
			{
				ch=pop();
				if((ch=='*')||(ch=='/')||(ch=='^'))
				{
					rexp[k++] = ',';
					rexp[k]=ch;
					k++;
					
					push(iexp[i]);
				}
				if((ch=='+')||(ch=='-')||(ch=='('))
				{
					push(ch);
					push(iexp[i]);
				}
			}
				break;
			case '+' : case '-' : if(isempty())push(iexp[i]);
			else
			{
				ch=pop();
				while((ch=='+')||(ch=='-')||(ch=='*')||(ch=='^')||(ch=='/'))
				{
					rexp[k++] = ',';
					rexp[k]=ch;
					k++;
					
					if(isempty())break;
					else ch=pop();   
				}
				if(ch=='(')push(ch);
				push(iexp[i]);
			}
				break;
			case ')' : ch=pop();
				while(ch!='(')
				{
					rexp[k++] = ',';
					rexp[k]=ch;
					k++;
					
					ch=pop();
				}
				break;
			default : if(!isdigit(iexp[i-1]) || !isdigit(iexp[i])) rexp[k++]=',';
				rexp[k]=iexp[i];
				k++;
				
				break;
		}
    }
    while(!isempty())
    {
		rexp[k++] = ',';
		rexp[k]=pop();
		k++;
    }
    rexp[k]='\0';
    printf("\nThe postfix expression is %s",rexp);
    return rexp;
	//return 0;
}
