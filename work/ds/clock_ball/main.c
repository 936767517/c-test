#include <stdio.h>
#include <unistd.h>

#include "stack.h"
#include "queue.h"

int main(void)
{
	int i;
	STACK min, five_min, hour;
	QUEUE ball;
	int value;
	int old;

	min = stack_create(4);
	if(NULL == min)
		goto fail1;
	five_min = stack_create(11);
	if(NULL == five_min)
		goto fail2;
	hour = stack_create(11);
	if(NULL == hour)
		goto fail3;
	ball = queue_create(27);
	if(NULL == ball)
		goto fail4;

	for(i = 1; i <= 27; i++)
	{
		queue_en(ball, &i);
	}

	while(1)
	{
		queue_front_and_de(ball, &value);
		if(!stack_is_full(min))
		{
			stack_push(min, &value);
		}
		else // min full
		{
			while(!stack_is_empty(min))
			{
				stack_top_and_pop(min, &old);
				queue_en(ball, &old);
			}
			if(!stack_is_full(five_min))
			{
				stack_push(five_min, &value);
			}
			else // five_min full
			{
				while(!stack_is_empty(five_min))
				{
					stack_top_and_pop(five_min, &old);
					queue_en(ball, &old);
				}
				if(!stack_is_full(hour))
				{
					stack_push(hour, &value);
				}
				else // hour full
				{
					while(!stack_is_empty(hour))
					{
						stack_top_and_pop(hour, &old);
						queue_en(ball, &old);
					}
					queue_en(ball, &value);
				}
			}
		}
		usleep(10000);
		printf("\33[10;20H\33[40m\33[37m");
		printf("%02d:%02d\n",hour->top+1, (five_min->top+1)*5+(min->top+1));
		printf("\33[0m");
	}


		queue_dispose(ball);
	fail4:
		stack_dispose(hour);
	fail3:
		stack_dispose(five_min);
	fail2:
		stack_dispose(min);
	fail1:
	
	return 0;
}
