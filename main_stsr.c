#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

	fp = serial_init(argc, argv);
	if (fp == -1) {
		printf("error open\n");
		return -1;
	}

	int cnt = 0;
	while (0 == exit_main) {
		unsigned char wv = cnt;
		char str[] = "abcdEf\r\n";
		char rstr[32];
		unsigned char rv;
		int len;
		len = strlen(str);
		int w = serial_write(str, len);
		if (w < 0) {
			printf("write error");
			break;
		}
		//printf("write ok\n");
		int r = serial_read(rstr, 32);
		if (r > 0) {
			//printf("%.2X\n", rv);
			serial_display(&rstr, r);
		} else {
			printf("dont recv\n");
			break;
		}
		//printf("sleep\n");
		sleep(1);
		cnt++;
	}
	serail_close();
	printf("\nexit\n");

	return 0;
}
