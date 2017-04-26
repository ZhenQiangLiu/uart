// written by Zhenqiang Liu
// modified by Qige Zhao @ 2017.04.26

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	const uart_dev = "/dev/ttyUSB0";
	const char *buf = "ABCDEFG\n";
	char rbuf[128];
	const unsigned int idle = 1;

	fd = uart_open(uart_dev);
	if (fd < 0) {
		printf("err> open uart failed.\n");
		return -1;
	}

	// exit when user wanted
	signal(SIGINT, 	(void *) main_exit); // ^c

	for(;;)
	{
		ret = uart_write(fd, buf, strlen(buf));
		if(ret > 0) {
			printf("PC urat_write %d bytes\n",ret);
		} else {
			printf("PC write fail\n");
		}
		sleep(idle);

		memset(rbuf, 0, sizeof(rbuf));
		ret = uart_read(fd, rbuf, sizeof(rbuf)-1);
		if(ret > 0) {
			printf("PC urat_read [%s]\n", rbuf);
		} else {
			printf("PC read fail\n");
		}
		sleep(idle);
	}
	return 0;
}
