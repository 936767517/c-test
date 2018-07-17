#include<stdio.h>
int  init_array(int arr_a[],int leg)
{
	int num;
	int i;
	for(i=0;i<leg;i++)
	{
		scanf("%d",&arr_a[i]);
	}
/*	for(i=0;1;i++)
	{
	scanf("%d",&num);
	arr_a[i]=num;
	if(i=leg-1)
	{
		break;	
	}

	}*/
}
int get_div(int arr_a[],int leg1,int arr_b[],int leg2)
{
	int i;
	for(i=0;i<leg2;i++)
	{
		if(arr_a[i]==0)
		{
			return -1;	
		}
	arr_b[i]=arr_a[i+1]/arr_a[i];
	}
	return 0;
}
int print_array_3(int arr_b[],int leg)
{
	int i;
	for(i=0;i<leg;i++)
	{
		printf("%d",arr_b[i]);
		if((i+1)%3==0)
		{
			printf("\n");	
		}
	}
	/*for(i=0;i<3;i++)
	{
		printf("%d %d %d\n",arr_b[0+3*i],arr_b[1+3*i],arr_b[2+3*i]);	
	}*/
}
int main(void)
{
	int arr_a[10];
	int arr_b[10];

	init_array(arr_a,10);
   
  if(0!=get_div(arr_a,10,arr_b,9))
  {
		printf("error");  
	}

	print_array_3(arr_b,9);
	
	return 0;	
}
