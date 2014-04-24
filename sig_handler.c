#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "g_param.h"

static void handler(int sig)
{
	switch (sig) {
	case SIGINT:
		exit_main = 1;
	break;
	default:
	break;
	}
}

int sig_proc(void)
{
	struct sigaction act;
	
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) < 0)	/* ctrl + C */
		return -1;
	return 0;
}

