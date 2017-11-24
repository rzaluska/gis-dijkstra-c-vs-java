#pragma once
#include<sys/time.h>

struct Timer {
    struct timeval start;
    struct timeval stop;
};

void timer_start(struct Timer *t);
void timer_stop(struct Timer *t);
unsigned long timer_get_usec_delta(struct Timer *t);
unsigned long timer_get_sec_delta(struct Timer *t);
