#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <unistd.h>

int main(int argc,char **argv)
{
	struct spwd *shdline;
	char *input_pass;
	char *crypted_pass;

	if(argc < 2)
	{
		fprintf(stderr,"Usage....\n");
		exit(1);
	}	

	input_pass = getpass("PASSWD:");
	/*if error*/

	shdline = getspnam(argv[1]);	
	/*if error*/

	crypted_pass = crypt(input_pass,shdline->sp_pwdp);
	/*if error*/
	
	if(strcmp(crypted_pass,shdline->sp_pwdp) == 0)
		puts("ok!");
	else
		puts("Error!");


	exit(0);
}


