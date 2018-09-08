#include<stdio.h>
int main(void)
{
	int xiao,mu,gong;
	printf("xiao\tmu\tgong\n");
	for(xiao=0;xiao<100;xiao++)
	{
		for(mu=0;mu<=33;mu++)
		{
			gong=100-xiao-mu;
			if(xiao%3==0&&gong>=0 && (100==xiao/3+3*mu+5*gong))
			{
				printf("%d\t%d\t%d\n",xiao,mu,gong);
			}
		}
	
	}

	return 0;
}
