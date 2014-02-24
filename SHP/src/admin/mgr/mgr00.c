/*
 * mgr00.c
 *
 *  Created on: Jan 6, 2014
 *      Author: zuoyan
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <libxml/tree.h>
#include <libxml/parser.h>

#include <wiringPi.h>

#include "admin/mgr00.h"

#include "log/lg00.h"

#include "mXBee/mXBee.h"
#include "mButton/mButton.h"
#include "mScreen/mScreen.h"

// Manager Info
MGR_INFO	prMgr;

// log4c
log4c_category_t* logcat = NULL;

// Button Status
int gButtonStatus = 0;

// Count
long gCount = 0;

// LCD Light Status
int gLCDLightStatus = 0;

/**********************/
/* main               */
/**********************/
int main(int argc, char *argv[])
{
	int	rc = 0;

	// Initialize MGR_INFO
	memset(&prMgr, 0x00, sizeof(prMgr));

	SysLogPut("!!!SHP Start~!!!");

	/**********************/
	/* Parameter Check    */
	/**********************/
	// TODO
	//rc = ParameterCheck();
	//if (rc != ADM_RC_NORMAL) {
	//	SysLogPut("Parameter Check Error!");
	//	puts("ParameterCheck Failed!");
	//	return ADM_RC_ERROR;
	//}
	//SysLogPut("Parameter Check OK!");
	//puts("Parameter Check OK!");

	/**********************/
	/* Initialization     */
	/**********************/
	rc = InitializeAdmin(&prMgr);
	if (rc != ADM_RC_NORMAL) {
		ErrorLogPut("InitializeAdmin Error!");

		return ADM_RC_ERROR;
	}

	SysLogPut("InitializeAdmin OK!");

	/**********************/
	/* Main Loop          */
	/**********************/
	rc = MainLoop();
	if (rc != ADM_RC_NORMAL) {
		ErrorLogPut("MainLoop Error!");

		return ADM_RC_ERROR;
	}

	SysLogPut("MainLoop OK!");

	/**********************/
	/* End                */
	/**********************/
	rc = FinalizeAdmin();
	if (rc != ADM_RC_NORMAL) {
		ErrorLogPut("FinalizeAdmin Error!");

		return ADM_RC_ERROR;
	}

	ErrorLogPut("FinalizeAdmin OK!");

	return ADM_RC_NORMAL;
}

/**********************/
/* ParameterCheck     */
/**********************/
int ParameterCheck()
{
	// TODO
	return ADM_RC_NORMAL;
}

/**********************/
/* InitializeAdmin    */
/**********************/
int InitializeAdmin()
{
	int rc = 0;

	// System Environment Initialize
	rc = SysEnvInit();
	if (rc != ADM_RC_NORMAL)
	{
		ErrorLogPut("System Environment Initialize Failed!");

		return ADM_RC_ERROR;
	}

	SysLogPut("System Environment Initialize OK!");

	// wiringPi Initialize
	rc = wiringPiSetupGpio();
	if (rc != ADM_RC_NORMAL)
	{
		ErrorLogPut("wiringPi Initialize Initialize Failed!");

		return ADM_RC_ERROR;
	}

	SysLogPut("wiringPi Initialize Initialize OK!");

	// Screen Module Initialize
	rc = mScreenInit();
	if (rc != ADM_RC_NORMAL)
	{
		ErrorLogPut("mScreen Module Initialize Failed!");

		return ADM_RC_ERROR;
	}

	SysLogPut("mScreen Module Initialize OK!");

	// Button Module Initialize
	rc = mButtonInit();
	if (rc != ADM_RC_NORMAL)
	{
		ErrorLogPut("mButtonInit Module Initialize Failed!");

		return ADM_RC_ERROR;
	}

	SysLogPut("mButtonInit Module Initialize OK!");

	// XBee Module Initialize
	rc = mXBeeInit();
	if (rc != ADM_RC_NORMAL)
	{
		ErrorLogPut("XBee Module Initialize Failed!");

		return ADM_RC_ERROR;
	}

	SysLogPut("XBee Module Initialize OK!");

	return ADM_RC_NORMAL;
}

/**********************/
/* MainLoop           */
/**********************/
int MainLoop()
{
//	int rc = 0;

	for (;;)
	{
		////////////////////////////
		// Check Button Status
		////////////////////////////
		switch (gButtonStatus)
		{
			case BUTTON_UP:
				SysLogPut("BUTTON_UP Pressed!");
				mScreenClear();
				mScreenDrawstring(0, 0, "BUTTON_UP Pressed!");
				mScreenDisplay();
				//printf("BUTTON_UP Pressed!\n");
				delay(500);
				break;
			case BUTTON_DOWN:
				SysLogPut("BUTTON_DOWN Pressed!");
				mScreenClear();
				mScreenDrawstring(0, 0, "BUTTON_DOWN Pressed!");
				mScreenDisplay();
				//printf("BUTTON_DOWN Pressed!\n");
				delay(100);
				break;
			case BUTTON_LEFT:
				SysLogPut("BUTTON_LEFT Pressed!");
				mScreenClear();
				mScreenDrawstring(0, 0, "BUTTON_LEFT Pressed!");
				mScreenDisplay();
				//printf("BUTTON_LEFT Pressed!\n");
				delay(100);
				break;
			case BUTTON_RIGHT:
				SysLogPut("BUTTON_RIGHT Pressed!");
				mScreenClear();
				mScreenDrawstring(0, 0, "BUTTON_RIGHT Pressed!");
				mScreenDisplay();
				//printf("BUTTON_RIGHT Pressed!\n");
				delay(100);
				break;
			case BUTTON_SELECT:
				SysLogPut("BUTTON_SELECT Pressed!");
				mScreenClear();
				mScreenDrawstring(0, 0, "BUTTON_SELECT Pressed!");
				mScreenDisplay();
				//printf("BUTTON_SELECT Pressed!\n");

				// TODO
				if (0 == gLCDLightStatus)
				{
					gLCDLightStatus = 1;
					mScreenSetLight(LCD_LIGHT_ON);
				} else
				{
					gLCDLightStatus = 0;
					mScreenSetLight(LCD_LIGHT_OFF);
				}

				delay(100);
				break;
			default:
				// SysLogPut("Nothing Pressed!");
				break;
		}

		// Clear Button Status
		gButtonStatus = 0;



		////////////////////////////
		// Reflash Screen
		////////////////////////////
		// TODO

		////////////////////////////
		// Check Moudel(PIR) Status
		////////////////////////////
		// TODO

		////////////////////////////
		// Check Battery Status
		////////////////////////////
		// TODO



	}

	return ADM_RC_NORMAL;
}

/**********************/
/* FinalizeAdmin      */
/**********************/
int FinalizeAdmin()
{
	int rc = 0;

	// Finalize XBee Module
	mXBeeClose();

	SysLogPut("XBee Module Finalize OK!");

	// System Environment Finalize
	rc = SysEnvFinal();
	if (rc != ADM_RC_NORMAL)
	{
		ErrorLogPut("System Environment Finalize Failed!");

		return ADM_RC_ERROR;
	}

	SysLogPut("System Environment Finalize OK!");

	return ADM_RC_NORMAL;
}


/**********************/
/* CheckMoudleStatus  */
/**********************/
int CheckModuleStatus()
{
	//int rc = 0;
	// TODO

	return ADM_RC_NORMAL;
}

/**********************/
/* SysEnvInit         */
/**********************/
int SysEnvInit()
{
	// Log Init
	SysLogInit();

	return ADM_RC_NORMAL;
}

/**********************/
/* SysEnvFinal        */
/**********************/
int SysEnvFinal()
{
	// Log Final
	SysLogClose();

	return ADM_RC_NORMAL;
}

/**********************/
/* GetSysEnv          */
/**********************/
int GetSysEnv()
{
	// TODO
	return ADM_RC_NORMAL;
}

