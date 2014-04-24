#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#include "g_param.h"
#include "sig_handler.h"

/*
	argv[1]: serial name, e.g.: /dev/ttyUSB0
	argv[2]: serial bps, e.g.: 9600
	argv[3]: display data mode, BM: binary mode, CM: character mode
*/
int main(int argc, char **argv)
{
	int fp;

	if (-1 == sig_proc()) {
		printf("error sig set\n");
		return -1;
	}

	fp = serial_conf(argc, argv);
	if (fp == -1) {
		printf("error open\n");
		return -1;
	}
	serial_fp = fp;


	int cnt = 0;
	while (0 == exit_main) {
		unsigned char wv = cnt;
		unsigned char rv;
		int len;
		len = 1;
		int w = write (fp, &wv, len);
		if (w < 0) {
			printf("write error");
			break;
		}
		//printf("write ok\n");
		int r = read(fp, &rv, 1);
		if (r == 1) {
			//printf("%.2X\n", rv);
			serial_display(&rv, 1);
			if (rv != wv) {
				printf("dont the orig value\n");
				break;
			}
		} else {
			printf("dont recv\n");
			break;
		}
		//printf("sleep\n");
		usleep(600);
		cnt++;
	}
	close(fp);
	printf("\nexit\n");

	return 0;
}
