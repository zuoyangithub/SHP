/*
 * mButton.c
 *
 *  Created on: Jan 6, 2014
 *      Author: zuoyan
 */

#include <wiringPi.h>

#include <errno.h>

#include "admin/mgr00.h"
#include "mButton/mButton.h"
#include "mScreen/mScreen.h"

#include "log/lg00.h"

/**********************/
/* PI_THREAD          */
/**********************/
PI_THREAD (mButtonThread)
{
	gButtonStatus = 0;
	gCount = 0;

	int iCurrentButton = 0;

	//(void)piHiPri(10);

	SysLogPut("mButtonThread living!");

	for(;;)
	{
		// Checking BUTTON_UP is pressed?
		iCurrentButton = digitalRead(BUTTON_UP);
		if(BUTTON_HIGH != iCurrentButton)
		{
			gButtonStatus = BUTTON_UP;
			gCount += 1;
//			delay(500);
		}

		// Checking BUTTON_DOWN is pressed?
		iCurrentButton = digitalRead(BUTTON_DOWN);
		if(BUTTON_HIGH != iCurrentButton)
		{
			gButtonStatus = BUTTON_DOWN;
			gCount += 1;
//			delay(500);
		}

		// Checking BUTTON_LEFT is pressed?
		iCurrentButton = digitalRead(BUTTON_LEFT);
		if(BUTTON_HIGH != iCurrentButton)
		{
			gButtonStatus = BUTTON_LEFT;
			gCount += 1;
//			delay(500);
		}

		// Checking BUTTON_RIGHT is pressed?
		iCurrentButton = digitalRead(BUTTON_RIGHT);
		if(BUTTON_HIGH != iCurrentButton)
		{
			gButtonStatus = BUTTON_RIGHT;
			gCount += 1;
//			delay(500);
		}

		// Checking BUTTON_SELECT is pressed?
		iCurrentButton = digitalRead(BUTTON_SELECT);
		if(BUTTON_HIGH != iCurrentButton)
		{
			gButtonStatus = BUTTON_SELECT;
			gCount += 1;
//			delay(500);
		}

		// Lock Signal for Update button status.
		//piLock(BUTTON_KEY);
	    //gButtonStatus = iCurrentButton;
	    //piUnlock(BUTTON_KEY);
	}

	return M_BUTTON_INIT_SUCCESS;
}

/**********************/
/* mButtonInit        */
/**********************/
int mButtonInit()
{
	int rc = 0;
	gButtonStatus = 0;

//	wiringPiSetup () ;
//	wiringPiSetupGpio();

	pinMode (BUTTON_UP, INPUT) ;
	pinMode (BUTTON_DOWN, INPUT) ;
	pinMode (BUTTON_LEFT, INPUT) ;
	pinMode (BUTTON_RIGHT, INPUT) ;
	pinMode (BUTTON_SELECT, INPUT) ;

	rc = piThreadCreate(mButtonThread);
	if(rc != M_BUTTON_INIT_SUCCESS)
	{
		ErrorLogPut("mButtonInit piThreadCreate Failed!");

		return M_BUTTON_INIT_FAILED;
	}

	SysLogPut("mButtonInit piThreadCreate OK!");

	return M_BUTTON_INIT_SUCCESS;
}

/**********************/
/* mButtonClose       */
/**********************/
void mButtonClose()
{
	// TODO
}

/**********************/
/* mButtonEvent       */
/**********************/
int mButtonEvent()
{
	// TODO

	return M_BUTTON_EVENT_SUCCESS;
}



