#ifndef __TIME_UTIL_H
#define __TIME_UTIL_H

#include <stdio.h>
#include <sys/time.h>
#include <sys/select.h>
#include <pthread.h>

struct timer_t {
    int delay;
    void (*fp)();
};

/**
 * Runs a timer using select. This function will
 * block if called directly.
 *
 * @param delay The number of seconds to delay.
 * @param fp The function to call when the timer ends.
 */
void run_timer(int delay, void (*fp)()) {
    struct timeval tv;

    tv.tv_sec = delay;
    tv.tv_usec = 0;

    select(0, NULL, NULL, NULL, &tv);

    if (fp != NULL)
        fp();
}

void *timer_callback(void * t) {
    struct timer_t * timer_s = (timer_t) t;

    run_timer(timer_s->delay, timer_s->fp, -1);

    return NULL;
}

/**
 * Runs a timer in a thread.
 *
 * @param delay The number of seconds to delay.
 * @param fp The function to call when the timer ends.
 */
void timer(int delay, void (*fp)()) {
    struct timer_t * timer_s = (struct timer_t *) malloc(sizeof(timer_s));
    timer_s->delay = delay;
    timer_s->fp = fp;

    pthread_t thread;
    pthread_create(&thread, NULL, timer_callback, timer_s);
}

#endif