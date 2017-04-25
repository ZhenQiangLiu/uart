/*
 * gws5k_task.c
 *
 *  Created on: Mar 14, 2017
 *  Updated on: Mar 14, 2017
 *  Maintainer: Qige Zhao
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <syslog.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "six_def.h"
#include "six_app.h"
#include "gws5k_task.h"
//#include "./include/six_uart.h"
#include "six_uart.h"


int FLAG_TASK_EXIT = 0;

// MAIN Calling sequences.
// - init()
// - run()
//
// if you want to fork a process, do it here;
int gws5k_task_Run(const void *env)
{
	APP_ENV *conf = (APP_ENV *)env;
	//int idle = conf->conf.idle ? conf->conf.idle : GWS5K_TASK_DFL_IDLE;
	int idle=0,fd=0,ret=0;
	char buf[10]={0};
	fd=uart_open("/dev/ttyS0");
	if(conf->conf.idle)
		idle=conf->conf.idle;
	else 
		idle=GWS5K_TASK_DFL_IDLE;
	for( ; ; ) {
		if ( FLAG_TASK_EXIT ) {
			break;
		}
		//printf("idle 1 %d\n",idle);
		bzero(buf,10);
		ret=uart_read(fd,buf,9);
		if(ret>0)
			printf("uart_read %s\n",buf);
		else
			printf("uart_read fail\n");
		sleep(idle);
		strcpy(buf,"abcdefghi");
		ret=uart_write(fd,buf,9);
		if(ret>0)
			printf("uart_write %d\n",ret);
		else
			printf("uart_write fail\n");
		//bzero(buf,10);
		
	}
	uart_close(&fd);
	return GWS5K_OK;
}


// call & reset signal(), tell your real executor, it's time to exit
// so hit ^c twice will interrupt right away
void gws5k_task_Signal(void)
{
	FLAG_TASK_EXIT = 1;
}
