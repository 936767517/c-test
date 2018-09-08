#include<stdio.h>
int main(void)
{
	char a,b;
	int sum;
	for(a='A';a<='C';a++)
	{
		for(b='X';b<='Z';b++)
		{
			
			sum=a+b;
			if(sum!='A'+'X'&&sum!='X'+'C'&&sum!='C'+'Z')
			{
				printf("%c+%c",a,b);
			}
		}
	
	}

	return 0;
}
