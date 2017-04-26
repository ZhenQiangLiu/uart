// written by Zhenqiang Liu
// modified by Qige Zhao @ 2017.04.26

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <termios.h>
#include <fcntl.h>

#include <signal.h>

#include "six_uart.h"

// uart file descriptor
static int fd = 0;

// handler of ^c, ^\, kill
void main_exit(void)
{
	uart_close(&fd);
	//kill(0, SIGQUIT);
}

// open device
// write, read
// close when exit
int main(void)
{
	int ret = 0;
	const char *uart_dev = "/dev/ttyUSB0";
	char tbuf[128], rbuf[128];
	const unsigned int idle = 1;

	// init & open uart
	fd = uart_open(uart_dev);
	if (fd < 0) {
		printf("err> open uart failed.\n");
		return -1;
	}

	// exit when user wanted
	signal(SIGINT, 	(void *) main_exit); // ^c

	for(;;)
	{
		memset(tbuf, 0, sizeof(tbuf));
		snprintf(tbuf, sizeof(tbuf), "ABCDEFG\n");
		ret = uart_write(fd, tbuf, strlen(tbuf));
		if(ret > 0) {
			printf("PC uart_write %d bytes\n",ret);
		} else {
			printf("PC uart_write fail\n");
		}
		sleep(idle);

		memset(rbuf, 0, sizeof(rbuf));
		ret = uart_read(fd, rbuf, sizeof(rbuf)-1);
		if(ret > 0) {
			printf("PC uart_read [%s]\n", rbuf);
		} else {
			printf("PC uart_read fail\n");
		}
		sleep(idle);
	}
	return 0;
}
