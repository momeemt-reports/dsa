#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct timer {
    double seconds;
    double ref;
    void (*reset)(struct timer *this_timer);
    void (*start)(struct timer *this_timer);
    void (*stop)(struct timer *this_timer);
    void (*display)(struct timer *this_timer);
    double (*result)(struct timer *this_timer);
} Timer;

Timer *new_timer();
void delete_timer(Timer *this_timer);

#endif  // __TIMER_H__
