#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef void mysem_t;

mysem_t *mysem_init(int initval);

int mysem_sub(mysem_t *ptr,int size);

int mysem_add(mysem_t *ptr,int size);

int mysem_destroy(mysem_t *ptr);



