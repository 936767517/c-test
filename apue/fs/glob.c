#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>

#define PAT		"/etc/a"
//#define PAT		"/etc/a*.conf"

int errfun_(const char *epath, int eerrno)
{
	fprintf(stderr,"%s:%s\n",epath,strerror(eerrno));
}

int main()
{
	glob_t globres;
	int i,err;

	err = glob(PAT,0,NULL/*errfun_*/,&globres);
	if(err)
	{
		fprintf(stderr,"glob() err = %d\n",err);
		exit(1);
	}

	for(i = 0 ; i < globres.gl_pathc; i++)
		puts(globres.gl_pathv[i]);

	globfree(&globres);

	exit(0);
}


