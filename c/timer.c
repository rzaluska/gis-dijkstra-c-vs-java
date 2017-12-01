#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stddef.h>
#include "timer.h"

void timer_start(struct Timer *t) {
    clock_gettime(CLOCK_MONOTONIC_RAW, &t->start);

}

void timer_stop(struct Timer *t) {
    clock_gettime(CLOCK_MONOTONIC_RAW, &t->stop);
}

long timer_get_usec_delta(struct Timer *t) {
    return (t->stop.tv_nsec - t->start.tv_nsec)/1000;
}

long timer_get_sec_delta(struct Timer *t) {
    return t->stop.tv_sec - t->start.tv_sec;
}

void timer_cumpute_delta(struct Timer * timer) {
    timer->delta_sec = timer_get_sec_delta(timer);
    if (timer->stop.tv_nsec < timer->start.tv_nsec) {
        timer->delta_sec--;
        timer->stop.tv_nsec += 1e9;
    }
    timer->delta_usec = timer_get_usec_delta(timer);
}

void timer_print(struct Timer *timer, char * tag) {
    timer_cumpute_delta(timer);
    printf("%s: %ld sec, %ld us\n", tag, timer->delta_sec, timer->delta_usec);
}
