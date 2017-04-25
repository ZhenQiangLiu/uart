#include "six_uart.h"
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

int fd=0;

void main_exit()
{
	uart_close(&fd);
	kill(0,SIGQUIT);
}

int main()
{
	int ret=0;
	char buf[10]={0};
	fd=uart_open("/dev/ttyUSB0");
	signal(SIGINT, 	(void *) main_exit);
	while(1)
	{
		bzero(buf,10);
		strcpy(buf,"ABCDEFGHI");
		ret=uart_write(fd,buf,9);
		if(ret>0)
			printf("PC urat_write %d\n",ret);
		else
			printf("PC write fail\n");
		bzero(buf,10);
		sleep(1);
		ret=uart_read(fd,buf,9);
		if(ret>0)
			printf("PC urat_read %s\n",buf);
		else
			printf("PC read fail\n");
	}
	return 0;
}
