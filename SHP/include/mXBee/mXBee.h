#define DEVICE "/dev/ttyAMA0"		// XBee RAW Device Address
#define BAUD 9600					// Serial Port Baud Rate

#define M_XBEE_INIT_ERROR -1

#define M_XBEE_INIT_SUCCESS 	0
#define M_XBEE_INIT_FAILED 		1

#define M_XBEE_CLOSE_SUCCESS 	0
#define M_XBEE_CLOSE_ERROR 		1

extern int mXBeeInit();
extern void mXBeeClose();
