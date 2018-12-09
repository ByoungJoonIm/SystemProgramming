#define COMMON_KEY 20181205
#define OUTBUFSIZE 1024

/*
 	this structure use for message queue
 */
typedef struct{
	long msg_type;
	char msg_buf[OUTBUFSIZE];
}MSG;
