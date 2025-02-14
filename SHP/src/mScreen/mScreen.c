/*
 * mScreen.c
 *
 *  Created on: Jan 6, 2014
 *      Author: zuoyan
 */

#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#include "admin/mgr00.h"

#include "mScreen/PCD8544/PCD8544.h"
#include "mScreen/mScreen.h"

#include "log/lg00.h"

const unsigned char SHP_logo [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xC0,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFE, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F, 0x1F, 0x1F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF8, 0xF0, 0xF0, 0xE3, 0xC3, 0xC3, 0x83,
0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC1, 0xC3, 0xC3, 0xC7, 0x0F, 0x0F, 0x1F, 0x3F,
0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xE0, 0xC0, 0xC0, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x03, 0x07, 0x07, 0x07, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00,
0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07,
0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#define SHP_LOGO_HEIGHT 48
#define SHP_LOGO_WIDTH  84


/**********************/
/* PI_THREAD          */
/**********************/
PI_THREAD (mScreenThread)
{

	for (;;)
	{
//		SysLogPut("mScreenThread living!");
//
//		mScreenDrawstring(0, 40, "mST OK!");
//		mScreenDisplay();
//
//		delay(10000);
	}

	return M_SCREEN_INIT_SUCCESS;
}

/**********************/
/* mScreenInit        */
/**********************/
int mScreenInit()
{
	int rc = 0;

	// Init and clear LCD
	LCDInit(PIN_SCLK, PIN_DIN, PIN_DC, PIN_CS, PIN_RST, 150);

	// LCDsetContrast
	LCDsetContrast(70);
	SysLogPut("mScreenInit LCDsetconstrast OK!");

	// LCD light on
	pinMode(PIN_LIGHT, OUTPUT);
	digitalWrite(PIN_LIGHT, HIGH);

//	digitalWrite(PIN_LIGHT, LOW);

	SysLogPut("mScreenInit LCDInit OK!");


	LCDclear();
	LCDdisplay();

	SysLogPut("mScreenInit LCDclear OK!");

	// Show logo
	//LCDshowLogo();

	// Show SHP Logo
	LCDdrawbitmap(0, 0, SHP_logo, SHP_LOGO_WIDTH, SHP_LOGO_HEIGHT, BLACK);
	LCDdisplay();

	SysLogPut("mScreenInit LCDshowLogo OK!");

	rc = piThreadCreate(mScreenThread);
	if(rc != M_SCREEN_INIT_SUCCESS)
	{
		ErrorLogPut("mScreenInit piThreadCreate Failed!");

		return M_SCREEN_INIT_FAILED;
	}

	SysLogPut("mScreenInit piThreadCreate OK!");

	return M_SCREEN_INIT_SUCCESS;
}

/**********************/
/* mScreenDrawstring  */
/**********************/
void mScreenDrawstring(int x, int y, char *c)
{
	LCDdrawstring(x, y, c);
}

/**********************/
/* mScreenDisplay     */
/**********************/
void mScreenDisplay(void)
{
	LCDdisplay();
}

/**********************/
/* mScreenClear       */
/**********************/
void mScreenClear(void)
{
	LCDclear();
}

/**********************/
/* mScreendrawstring  */
/**********************/
void mScreenSetCursor(int x, int y)
{
	LCDsetCursor(x, y);
}

/**********************/
/* mScreenSetLight    */
/**********************/
void mScreenSetLight(int l)
{
	digitalWrite(PIN_LIGHT, l);
}

/**********************/
/* mScreenShowLogo    */
/**********************/
void mScreenShowLogo()
{
	LCDclear();
	LCDdrawbitmap(0, 0, SHP_logo, SHP_LOGO_WIDTH, SHP_LOGO_HEIGHT, BLACK);

	LCDdisplay();
}


/**********************/
/* mScreenClose       */
/**********************/
void mScreenClose()
{
	LCDclear();

	LCDdisplay();
	// LCD light off
	digitalWrite(PIN_LIGHT, LOW);
}
