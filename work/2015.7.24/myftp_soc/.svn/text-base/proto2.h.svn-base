#ifndef PROTO_H__
#define PROTO_H__

#define KEYPATH		"/etc/hosts"
#define KEYPROJ		'e'		

#define PATHSIZE	1024
#define DATASIZE	1024

enum
{
	MSG_PATH=1,
	MSG_S2C,
};

typedef struct msg_path_st
{
	long mtype;				/*must MSG_PATH*/	
	char path[PATHSIZE];	/*ASCIIZ带尾0的串*/
}msg_path_t;

typedef struct msg_s2c_st
{
	long mtype;				/*must MSG_S2C*/	
	int datalen;
	/*
 *		datalen > 0		:data
 *				== 0	:eot
 *				< 0		:-errno
 * */
	char data[DATASIZE];
}msg_data_t;


#endif

