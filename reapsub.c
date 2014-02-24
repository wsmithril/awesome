/*
 * Make all process started by awesome be a child process of awesome its self
 * Inspired by
 * http://lilydjwg.is-programmer.com/2014/2/23/let-s-adopt-orphaned-processes.43035.html
 *
 */

#include <sys/prctl.h>

#ifdef PR_SET_CHILD_SUBREAPER
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "reapsub.h"

int set_reap_subprocess(void) {
    int ret = 0;

    // ignore SIGCHLD to allow awesome to reap dead chiild
    signal(SIGCHLD, SIG_IGN);

    // set awesome to reap any child process
    if ((ret = prctl(PR_SET_CHILD_SUBREAPER, 1))) {
        perror("Error setting PR_SET_CHILD_SUBREAPER to 1");
        return ret;
    }

    return 0;
}


#endif /* PR_SET_CHILD_SUBREAPER */

