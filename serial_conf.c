#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>

#include "g_param.h"

static int dm = -1;

int serial_conf(int argc, char **argv)
{
	int fp;
	int status;
	char *serial_name;
	int bps;
	struct termios options;

	if (argc < 4)
		goto ff;

	serial_name = argv[1];

	if (0 == strcmp(argv[2], "9600"))
		bps = B9600;
	else if (0 == strcmp(argv[2], "38400"))
		bps = B38400;
	else if (0 == strcmp(argv[2], "115200"))
		bps = B115200;
	else {
		printf("Don't know the bps \"%s\"\n", argv[2]);
		goto ff;
	}

	if (0 == strcmp(argv[3], "BM"))
		dm = 0;
	else if (0 == strcmp(argv[3], "CM"))
		dm = 1;
	else {
		printf("Don't know the data mode \"%s\"\n", argv[3]);
		goto ff;
	}

	fp = open(serial_name, O_RDWR);

	if (fp == -1)
		goto ff;

	tcgetattr(fp,&options);
	cfmakeraw(&options);
	cfsetispeed(&options, bps);
	cfsetospeed(&options, bps);

	//8N1
	options.c_cflag |= CLOCAL|CREAD;
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

	options.c_cc[VTIME] = 1;
	options.c_cc[VMIN] = 0;

	tcflush(fp, TCIOFLUSH);
	status = tcsetattr(fp, TCSANOW, &options);
	if (status != 0) {
		perror(strerror(errno));
		goto fail;
	}
	tcflush(fp, TCIOFLUSH);
	return fp;

fail:
	close(fp);
ff:
	return -1;
}

void serial_display(unsigned char *buf, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		if (0 == dm)
			printf ("%.2X ", buf[i]);
		else if (1 == dm)
			printf ("%c ", buf[i]);
	
	}
	//setbuf(stdout, NULL);	//fflush stdin
	fflush(stdout);
}
