#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int stack[1024] = {0};
int head = 0;

void pmpush(int data)
{
	stack[head]=data;
	head++;
}

int pmpull()
{
	head--;
	return stack[head];
}

void pmnum(FILE * f, int c)
{
	int res = c-'0';
	while((c=getc(f))!=' ' && c!='\n' && c!=EOF)
	{
		res*=10;
		res+=c-'0';
	}
	pmpush(res);
}

void pmadd()	
{
	int b = pmpull();
	int a = pmpull();
	pmpush(a+b);
}

void pmsub()
{
	int b = pmpull();
	int a = pmpull();
	pmpush(a-b);
}

void pmmul()
{
	int b = pmpull();
	int a = pmpull();
	pmpush(a*b);
}

void pmdiv()
{
	int b = pmpull();
	int a = pmpull();
	pmpush(a/b);
}

void pmmod()
{
	int b = pmpull();
	int a = pmpull();
	pmpush(a%b);
}

void pmexp()
{
	int b = pmpull();
	int a = pmpull();
	int res = 1;
	while(b>0)
	{
		res*=a;
		b--;
	}
	pmpush(res);
}

void pmout()
{
	printf("%d\n",pmpull());
}

void main()
{
	FILE* f = fopen("in.txt","r");
	if(f==NULL)
	{
		puts("File error");
		exit(1);
	}
	int c;
	while((c=fgetc(f))!=EOF)
	{
		if(c==' ' || c=='\n')
		{
			continue;
		} else
		if(isdigit(c))
		{
			pmnum(f,c);
		} else
		if(c=='+')
		{
			pmadd();
		} else
		if(c=='-')
		{
			pmsub();
		} else
		if(c=='*')
		{
			pmmul();
		} else
		if(c=='/')
		{
			pmdiv();
		} else
		if(c=='%')
		{
			pmmod();
		} else
		if(c=='^')
		{
			pmexp();
		} else
		if(c=='#')
		{
			pmout();
		} else
		{
			puts("Syntax error");
		}
	}
	fclose(f);	
}
