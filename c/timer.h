#pragma once
#include<sys/time.h>

struct Timer {
    struct timespec start;
    struct timespec stop;
    long delta_sec;
    long delta_usec;
};

void timer_start(struct Timer *t);
void timer_stop(struct Timer *t);
long timer_get_usec_delta(struct Timer *t);
long timer_get_sec_delta(struct Timer *t);
void timer_print(struct Timer *t, char * tag);
