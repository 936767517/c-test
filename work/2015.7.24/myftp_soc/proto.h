#ifndef PROTO_H__
#define PROTO_H__

#include <sys/msg.h>
#define KEYPATH		"/etc/hosts"
#define KEYPROJ		'e'		
#define RCVPORT "1989"
#define SEDPORT "1990"
#define PATHSIZE	1024
#define DATASIZE	10

enum
{
	MSG_PATH=1,
	MSG_DATA,
	MSG_ERR,
	MSG_EOT
};

struct msg_path_st
{
	uint32_t mtype;				/*must MSG_PATH*/	
	uint8_t path[PATHSIZE];	/*ASCIIZ带尾0的串*/
}__attribute__((packed)) ;
typedef struct msg_path_st msg_path_t;
struct msg_data_st
{
	uint32_t mtype;				/*must MSG_DATA*/	
	uint32_t datalen;
	uint8_t data[DATASIZE];
}__attribute__((packed));
typedef struct msg_data_st msg_data_t;

struct msg_err_st
{
	uint32_t mtype;				/*must MSG_ERR*/	
	uint32_t err;
}__attribute__((packed));
typedef struct msg_err_st msg_err_t;

struct msg_eot_st
{
	uint32_t mtype;				/*must MSG_EOT*/	
}__attribute__((packed)) ;
typedef struct msg_eot_st msg_eot_t;

union msg_s2c_un
{
	long mtype;
	msg_data_t datamsg;
	msg_err_t errmsg;
	msg_eot_t eotmsg;
};


#endif
