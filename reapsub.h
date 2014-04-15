#ifndef __REAPSUB_H__
#define __REAPSUB_H__
#include <sys/prctl.h>

int check_kernel_above_3_4(void);

#ifdef PR_SET_CHILD_SUBREAPER

int set_reap_subprocess(void);

#endif /* PR_SET_CHILD_SUBREAPER */
#endif
