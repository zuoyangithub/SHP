#include <log4c.h>

#define ADM_RC_NORMAL	0
#define	ADM_RC_ERROR	-1

struct tagMGR_INFO {
	long	lAdmBuffSize;		/* XXXXXXX */
	char	admBuff;			/* XXXXXXX */
	int		iId;				/* XXXXXXX */
	int		iXBee_FD;			/* XBee Module file descriptor */
};
typedef struct tagMGR_INFO MGR_INFO;

/////////////////////////////////
// Global Variable
/////////////////////////////////

// Manager Info
extern MGR_INFO	prMgr;

// log4c
extern log4c_category_t* logcat;

// Button Status
extern int gButtonStatus;

// Count
extern long gCount;

// LCD Light Status
extern int gLCDLightStatus;

int main(int argc, char *argv[]);

int ParameterCheck();
int InitializeAdmin();
int MainLoop();
int FinalizeAdmin();

int SysEnvInit();
int SysEnvFinal();

int GetSysEnv();
int SetSysEnv();

int CheckModuleStatus();


