#include <stdio.h>
int bit(char a[])
{
	int i=0;
	while(1)
	{
		if(a[i]=='\0')
		{
			return i;	
		}
		i++;
	}
}
int main(void)
{
	char a[20];
	char b[20];
	scanf("%s %s",a,b);
//	printf("%s\n",b);
	int num1=bit(a);
	printf("%d\n",num1);
	int num2=bit(b);
	int i;
		for(i=0;i<5;i++)
		{
			a[num1+i]=b[i];
			if(b[i]=='\0')
			{
				break;	
			}
		//	printf("%c\n",a[num1+i]);
		}
		printf("i=%d\n",i);
		a[num1+i]='\0';
	//	printf("%c\n",a[num1]);
	printf("%s\n",a);
	
	return 0;	
}
