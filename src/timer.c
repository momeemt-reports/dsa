#include "timer.h"

void timer_reset(Timer *this_timer) {
    this_timer->seconds = 0.0;
    this_timer->ref = 0.0;
    // printf("Timer reset\n");
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    // printf("Time precision:\t%ld.%09ld sec\n", (long)ts.tv_sec, ts.tv_nsec);
}

void timer_start(Timer *this_timer) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    this_timer->ref = (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

void timer_stop(Timer *this_timer) {
    this_timer->seconds -= this_timer->ref;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    this_timer->ref = (double)(ts.tv_sec) + (double)ts.tv_nsec * 1e-9;
    this_timer->seconds += this_timer->ref;
}

void timer_display(Timer *this_timer) {
    printf("Elapsed time: \t%lf sec\n", this_timer->seconds);
}

double timer_result(Timer *this_timer) { return this_timer->seconds; }

Timer *new_timer() {
    Timer *this_timer = (Timer *)malloc(sizeof(Timer));
    this_timer->seconds = 0.0;
    this_timer->ref = 0.0;
    this_timer->reset = timer_reset;
    this_timer->start = timer_start;
    this_timer->stop = timer_stop;
    this_timer->display = timer_display;
    this_timer->result = timer_result;
    return this_timer;
}

void delete_timer(Timer *this_timer) { free(this_timer); }
