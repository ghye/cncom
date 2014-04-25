#ifndef __SERAIL_CONF_H__
#define __SERAIL_CONF_H__

int serial_init(int argc, char **argv);
int serial_write(unsigned char *buf, int len);
int serial_read(unsigned char *buf, int len);
int serail_close(void);
void serial_display(unsigned char *buf, int len);

#endif
