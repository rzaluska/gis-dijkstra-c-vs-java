#include <sys/time.h>
#include <stddef.h>
#include "timer.h"

void timer_start(struct Timer *t) {
    gettimeofday(&t->start, NULL);
}

void timer_stop(struct Timer *t) {
    gettimeofday(&t->stop, NULL);
}

unsigned long timer_get_usec_delta(struct Timer *t) {
    return t->stop.tv_usec - t->start.tv_usec;
}

unsigned long timer_get_sec_delta(struct Timer *t) {
    return t->stop.tv_sec - t->start.tv_sec;
}
