#include <sys/prctl.h>

#ifdef PR_SET_CHILD_SUBREAPER

int set_reap_subprocess(void);

#endif /* PR_SET_CHILD_SUBREAPER */

