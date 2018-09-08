#include <stdio.h>
int get(ch)
{
	if(ch>='a'&&ch<='z')
	{
		return (ch-'a');	
	}
	if(ch>='A'&&ch<='Z')
	{
		return (ch-'A');	
	}
	else 
	{
		return -1;
	}
}

int main(void)
{
	int num [26]={};
	char ch;
	int i;
	while(1)
	{
		scanf("%c",&ch);
		if (ch=='0')
		{
			break;	
		}
		int res=get(ch);
		if(res!=(-1))
		{
		num[res]++;
		}
	/*	switch(ch)
			{
			case 'a':case 'A': num[0]++;break;
			case 'b':case 'B': num[1]++;break;
			case 'c':case 'C': num[2]++;break;
			case 'D':case 'd': num[3]++;break;
			case 'e':case 'E': num[4]++;break;
			case 'f':case 'F': num[5]++;break;
			case 'g':case 'G': num[6]++;break;
			case 'h':case 'H': num[7]++;break;
			case 'i':case 'I': num[8]++;break;
			case 'j':case 'J': num[9]++;break;
			case 'k':case 'K': num[10]++;break;
			case 'l':case 'L': num[11]++;break;
			case 'm':case 'M': num[12]++;break;
		    case 'n':case 'N': num[13]++;break;
			case 'o':case 'O': num[14]++;break;
			case 'p':case 'P': num[15]++;break;
			case 'q':case 'Q': num[16]++;break;
			case 'r':case 'R': num[17]++;break;
			case 's':case 'S': num[18]++;break;
			case 't':case 'T': num[19]++;break;
			case 'u':case 'U': num[20]++;break;
			case 'v':case 'V': num[21]++;break;
			case 'w':case 'W': num[22]++;break;
			case 'x':case 'X': num[23]++;break;
			case 'y':case 'Y': num[24]++;break;
			case 'z':case 'Z': num[25]++;break;
			default:
				break;
		}*/
	}
	for(i=0;i<26;i++)
	{
		if(num[i]!=0)
		{
		printf("num[%c]=%d ",i+'a',num[i]);	
		}
	}
	printf("\n");
	return 0;	
}
