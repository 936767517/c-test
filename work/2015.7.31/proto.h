#ifndef PROTO_H__
#define PROTO_H__

#define DEFAULT_MGROUP		"224.2.2.5"
#define DEFAULT_PORT		"1989"

typedef uint8_t chnid_t;

#define NR_CHN				200
#define CHNID_LIST			0
#define MINCHNID			1
#define MAXCHNID			(MINCHNID+NR_CHN-1)

#define MAX_MSG				(65536-60-8)
#define MAX_DATA			((MAX_MSG)-sizeof(uint8_t))
#define MAX_ENTRY			((MAX_MSG)-sizeof(uint8_t))

struct msg_channel_st
{
	chnid_t chnid;			/*MUST BE [MINCHNID,MAXCHNID]*/
	uint8_t data[MAX_MSG];
}__attribute__((packed));

struct list_entry_st
{
	chnid_t chnid;          /*MUST BE [MINCHNID,MAXCHNID]*/
//	len;
	uint8_t desc[1];
}__attribute__((packed));

struct msg_list_st
{
	chnid_t chnid; 			/* MSUT BE CHNID_LIST */
	struct list_entry_st entry[1];
}__attribute__((packed));

#endif



