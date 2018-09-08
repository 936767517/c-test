
/*
 *	-M          指定多播地址
 *	-P			指定测试用端口
 *	-F			前台调试运行
 *	-D			指定调试频道
 *	-H          显示帮助
 *
 * */

int main(int argc,char **argv)
{
	struct mlib_chn_st *listptr;
	int listsize;

	/* conf处理	*/

	/* socket 初始化 */

	/* 获取频道列表（从media中获取）*/
	if(mlib_getchnlist(&listptr,&listsize) < 0)
	{
		syslog();
	}


	/* 创建thr_list	*/
	thr_list_create();
	/*if error*/


	/* 创建thr_channel*/
	/*1:200   10:200   200:200*/

	for(i = 0 ; i < listsize ; i++)
	{
		thr_channel_create();
	}

	while(1)
		pause();

	exit(0);
}

