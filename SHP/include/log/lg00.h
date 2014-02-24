#define SYSLOG_RC_NORMAL	0
#define	SYSLOG_RC_ERROR		-1

extern void SysLogInit();

extern void SysLogPut(char *);
extern void ErrorLogPut(char *);

extern void SysLogClose();

