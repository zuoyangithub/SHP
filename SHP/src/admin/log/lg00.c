/*
 * lg00.c
 *
 *  Created on: Jan 7, 2014
 *      Author: zuoyan
 */
#include <log4c.h>

#include "admin/mgr00.h"
#include "log/lg00.h"

extern void SysLogInit()
{
	//puts("In SysLogInit");

	log4c_init();

	logcat = log4c_category_get("SHP");

	//printf("logcat=%p\n", logcat);
}

extern void ErrorLogPut(char *ptLog)
{
	//puts("In ErrorLogPut");
	//puts(ptLog);

	//TODO
	log4c_category_log(logcat, LOG4C_PRIORITY_ERROR, ptLog);

	//printf("logcat=%p\n", logcat);
}

extern void SysLogPut(char *ptLog)
{
	//puts("In SysLogPut");
	//puts(ptLog);

	//TODO
	log4c_category_log(logcat, LOG4C_PRIORITY_INFO, ptLog);

	//printf("logcat=%p\n", logcat);
}

extern void SysLogClose()
{
	//puts("In SysLogClose");

	log4c_fini();

	//printf("logcat=%p\n", logcat);
}

