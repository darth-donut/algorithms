#ifndef _UTIL_H_
#define _UTIL_H_

#include "list.h"
#include "ram.h"

#define ERR_CHN stderr

void *smalloc(const size_t n);

void *scalloc(const size_t nmemb, const size_t size);

void *srealloc(void *old, const size_t new_size);

void error_msg(const char *msg, int exit_b);

void print_debug_pid(List lst, const char *msg);

void disp_ram(Ram ram);

void print(unsigned time, int pid, unsigned num_procs, unsigned num_holes, unsigned mem_usage);

void assert_100(Ram ram);

#endif      // end of _UTIL_H_ guard
