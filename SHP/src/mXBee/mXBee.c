#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/usr/include/xbee.h"

#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>

#include "admin/mgr00.h"
#include "log/lg00.h"
#include "mXBee/mXBee.h"
//#include "mXBee/xbee.h"

void myCB(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
    xbee_err ret;
        int value;

    if ((ret = xbee_pktAnalogGet(*pkt, 0, 0, &value)) != XBEE_ENONE && ret != XBEE_ENOTEXISTS) {
                       printf("xbee_pktAnalogGet(channel=%d): ret %d\n", 0, ret);
               } else if (ret != XBEE_ENOTEXISTS) {
                       printf("A%d: %d\n", 0, value);
               }


}

int mXBeeInit()
{

	printf("xbee inti start here!\n");

	xbee_err ret;
	struct xbee *xbee;

//	if ((ret = xbee_setup(&xbee, "xbeeZB", "/dev/ttyAMA0", 57600)) != XBEE_ENONE) {
	if ((ret = xbee_setup(&xbee, "xbeeZB", "/dev/ttyAMA0", 57600)) != XBEE_ENONE) {
	        printf("xbee_setup(): %d - %s\n", ret, xbee_errorToStr(ret));
	        return ret;
	}

	printf("xbee setup over!\n");


	/* use libxbee */
//	connection type 0 - Transmit Status
//	connection type 1 - Modem Status
//	connection type 2 - Local AT
//	connection type 3 - Remote AT
//	connection type 4 - Data
//	connection type 5 - Data (explicit)
//	connection type 6 - I/O
//	connection type 7 - Sensor
//	connection type 8 - Identify
//	connection type 9 - OTA Update Status

	struct xbee_con *con;
	struct xbee_conAddress address;
	 unsigned char txRet;


	/* initialize xbee, using xbee_setup() */

	memset(&address, 0, sizeof(address));
	address.addr64_enabled = 1;
	  address.addr64[0] = 0x00;
	  address.addr64[1] = 0x13;
	  address.addr64[2] = 0xA2;
	  address.addr64[3] = 0x00;
	  address.addr64[4] = 0x40;
	  address.addr64[5] = 0x9B;
	  address.addr64[6] = 0x80;
	  address.addr64[7] = 0x04;

	if ((ret = xbee_conNew(xbee, &con, "Remote AT", &address)) != XBEE_ENONE)
	{
		printf("xbee_conNew(): %d - %s\n", ret, xbee_errorToStr(ret));
		return ret;
	}

	printf("xbee connect over!\n");


    if ((ret = xbee_conCallbackSet(con, myCB, NULL)) != XBEE_ENONE) {
            xbee_log(xbee, -1, "xbee_conCallbackSet() returned: %d", ret);
            return ret;
    }

    printf("call backset over!\n");

    if ((ret = xbee_conTx(con, &txRet, "IS")) != XBEE_ENONE) {
            xbee_log(xbee, -1, "xbee_conTx() returned: %d", ret);
            return ret;
    }
    printf("xbee conTx over!\n");

        usleep(1000000);

    if ((ret = xbee_conEnd(con)) != XBEE_ENONE) {
            xbee_log(xbee, -1, "xbee_conEnd() returned: %d", ret);
            return ret;
    }

    printf("xbee end connect over!\n");

    xbee_shutdown(xbee);

    printf("xbee shutdown over!\n");







//	struct xbee_pkt *pkt;
//
////	pkt = malloc(sizeof(struct xbee_pkt));
//
////	pkt->xbee = xbee;
////	pkt->con =con;
//	//pkt->conType = "Data";
//
//
////	pkt->address.addr64[0] = address.addr64[0];
////	pkt->address.addr64[1] = address.addr64[1];
////	pkt->address.addr64[2] = address.addr64[2];
////	pkt->address.addr64[3] = address.addr64[3];
////	pkt->address.addr64[4] = address.addr64[4];
//	pkt->address.addr64[5] = address.addr64[5];
//	pkt->address.addr64[6] = address.addr64[6];
//	pkt->address.addr64[7] = address.addr64[7];

//	int value;
//
//	/* receive a packet with analog I/O data, using xbee_conRx() */
//
//	if ((ret = xbee_pktAnalogGet(pkt, 3, 0, &value)) != XBEE_ENONE)
//	{
//		printf("xbee_pktAnalogGet(): %d - %s\n", ret, xbee_errorToStr(ret));
//		free(pkt);
//		return ret;
//	}
//
//	/* 'value' now contains the ADC value from the A3 pin */
//
//	printf("A0 is:%d\n", value);
//
//
//	printf("xbee get analog  over!\n");
//
//
//
//	if ((ret = xbee_conEnd(con)) != XBEE_ENONE)
//	{
//		printf("xbee_conEnd(): %d - %s\n", ret, xbee_errorToStr(ret));
//		free(pkt);
//		return ret;
//	}
//
//	printf("xbee end connect over!\n");
//
//	if ((ret = xbee_shutdown(xbee)) != XBEE_ENONE) {
//        printf("xbee_shutdown(): %d - %s\n", ret, xbee_errorToStr(ret));
//    	free(pkt);
//        return ret;
//	}
//
//	printf("xbee close over!\n");
//
//	free(pkt);

	return M_XBEE_INIT_SUCCESS;
}

int mXBeeInit_bk()
{
//	prMgr.iXBee_FD = serialOpen (DEVICE, BAUD);
//	printf("iXBee_FD=%d", prMgr.iXBee_FD);
//
//	// -1 for any error.
//	if (prMgr.iXBee_FD == M_XBEE_INIT_ERROR)
//	{
//		ErrorLogPut("Initialization Error!");
//		printf("errno=%d\n", errno);
//
//		return M_XBEE_INIT_FAILED;
//	}

//	  struct xbee *xbee;
//	  char **conTypes;
//	  xbee_err ret;
//	  int i;
//
//	  if ((ret = xbee_setup(&xbee, "xbee1", "/dev/ttyAMA0", 57600)) != XBEE_ENONE) {
//	    printf("ret: %d (%s)\n", ret, xbee_errorToStr(ret));
//	    return ret;
//	  }
//
//	  if ((ret = xbee_conGetTypes(xbee, &conTypes)) != XBEE_ENONE) {
//	    printf("ret: %d (%s)\n", ret, xbee_errorToStr(ret));
//	    return ret;
//	  }
//
//	  for (i = 0; conTypes[i]; i++) {
//	    printf("connection type %d - %s\n", i, conTypes[i]);
//	  }
//
//	  free(conTypes);
//
//	  xbee_shutdown(xbee);

	int rc = 0;

	  struct xbee *xbee;
	  struct xbee_con *con;
	  struct xbee_conAddress address;

	  /* setup libxbee, using a Series 1 XBee, on /dev/ttyUSB0, at 57600 baud */
	  rc = xbee_setup(&xbee, "xbee3", "/dev/ttyAMA0", 57600);
	  printf("xbee_setup rc=%d\n", rc);

	  /* setup a 64-bit address */
	  memset(&address, 0, sizeof(address));
	  address.addr64_enabled = 1;
	  address.addr64[0] = 0x00;
	  address.addr64[1] = 0x13;
	  address.addr64[2] = 0xA2;
	  address.addr64[3] = 0x00;
	  address.addr64[4] = 0x40;
	  address.addr64[5] = 0x9B;
	  address.addr64[6] = 0x80;
	  address.addr64[7] = 0x24;

	  /* create a 64-bit data connection with the address */
	  rc = xbee_conNew(xbee, &con, "64-bit Data", &address);
	  printf("xbee_conNew rc=%d\n", rc);

	  /* setup a callback to keep both the system load and response time low */
	  rc = xbee_conCallbackSet(con, myCB, NULL);
	  printf("xbee_conCallbackSet rc=%d\n", rc);

	  /* sleep for a minute! */
	  delay(60000);

	  /* close the connection */
	  rc = xbee_conEnd(con);
	  printf("xbee_conEnd rc=%d\n", rc);

	  /* shutdown libxbee */
	  rc = xbee_shutdown(xbee);
	  printf("xbee_shutdown rc=%d\n", rc);
//	  printf("shutdown libxbee\n");


	return M_XBEE_INIT_SUCCESS;
}

void mXBeeClose()
{
//	serialClose(prMgr.iXBee_FD);
}
