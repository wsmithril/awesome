/*
 * Make all process started by awesome be a child process of awesome its self
 * Inspired by
 * http://lilydjwg.is-programmer.com/2014/2/23/let-s-adopt-orphaned-processes.43035.html
 *
 */

#include <sys/prctl.h>

#include <string.h>
#include <sys/utsname.h>

#include "reapsub.h"
int check_kernel_above_3_4(void) {
    int major = 0, minor = 0;
    struct utsname uts;
    uname(&uts);

    // parse uts.release
    const char * release = uts.release;
    int p = 0;
#define isnum(c) ((c) <= '9' && (c) >= '0')
    while (release[p] && isnum(release[p]))
        major = major * 10 + release[p++] - '0';
    p++;
    while (release[p] && isnum(release[p]))
        minor = minor * 10 + release[p++] - '0';

    if (major >= 3 && minor >= 4) {
        return 0;
    } else {
        return 1;
    }
#undef isnum
}

#ifdef PR_SET_CHILD_SUBREAPER
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>


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

