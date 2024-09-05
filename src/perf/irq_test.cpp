#include <csignal>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

#define POSIX_TIME_TEST

namespace {

void busyCpu()
{
    timespec tpstart;
    timespec tpend;
    long timediff;
    static int isPrinted = false;

    ::clock_gettime(CLOCK_MONOTONIC, &tpstart);

    volatile long long i;
    for (i = 0; i < 3000; ++i)
    {
        // Loop 3000: 95 us / CPU 25 %
    }

    ::clock_gettime(CLOCK_MONOTONIC, &tpend);
    timediff = 1000 * 1000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec-tpstart.tv_nsec) / 1000;

    if (!isPrinted)
    {
        ::printf("Busy time: %ld us\n", timediff);
        isPrinted = true;
    }

}

#ifdef POSIX_TIME_TEST
void posixTimerSignal(int sig, siginfo_t *si, void *pri)
{
    static int i = 0;
    static int count = 0;

    /*
    Test result: ./vmstat 1
    procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
    r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
    1  0      0 439600   3408  37992    0    0     0     0  213  705  1  2 98  0  0
    1  0      0 439408   3416  37996    0    0     0     0 2288 6947 38  1 61  0  0 >> Restart serval times, CPU load increased.
    1  0      0 439408   3416  37996    0    0     0     0 2290 6798 38  0 62  0  0
    1  0      0 439408   3416  37996    0    0     0     0 2301 6915 37  1 61  0  0
    */
    busyCpu();
    if (i++ == 2000)
    {
        ::printf("posix_timer: %d\n", count++);
        i = 0;
    }
}

void posixTimerTest()
{
    timer_t timer = {0};
    struct sigevent sev = {0};
    struct sigaction sa = {0};

    const struct timespec timeVal = {
          .tv_sec = 0,
          .tv_nsec = 500 * 1000 // 500 us
    };

    const struct itimerspec its =
    {
        .it_interval = timeVal,
        .it_value = timeVal
    };

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timer;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = posixTimerSignal;

    if(::sigemptyset(&sa.sa_mask) == -1)
    {
        ::perror("sigemptyset error");
    }

    if(::sigaction(SIGRTMIN, &sa, nullptr) == -1)
    {
        ::perror("sigaciton error");
    }

    if(::timer_create(CLOCK_REALTIME, &sev, &timer) != 0)
    {
        ::perror("timer_create error");
    }

    if(::timer_settime(timer, 0, &its, nullptr) != 0)
    {
        ::perror("timer_settime error");
    }

    while (true)
    {
        ::pause();
    }

}
#endif

}

int main(int argc, char *argv[])
{

#ifdef POSIX_TIME_TEST
    posixTimerTest();
#endif

    return EXIT_SUCCESS;
}
