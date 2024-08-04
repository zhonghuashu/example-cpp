/**
 * @file mssleep.cpp
 * @brief 利用nanosleep函数实现毫秒级函数
 * @author Shu, Zhong Hua
 * @date 2023-10-14
 */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#define ms_sleep 5000

void mssleep(unsigned long ms);

void termSignal(int sig)
{
    printf("I got signal %d\n", sig);

    // CTRL-C again, terminate program because of default signal handler behavior.
    // signal(SIGINT, SIG_DFL);
}

int main(int argc, char *argv[])
{
    ::printf("Use signal\n");
    ::signal(SIGINT, termSignal);

    while (true)
    {
        mssleep(ms_sleep);
        printf("5 seconds passed...\n");
    }
    return 0;
}

void mssleep(unsigned long ms)
{
    struct timespec ts = {
          .tv_sec = (long int)(ms / 1000),
          .tv_nsec = (long int)(ms % 1000) * 1000000L
    };

    unsigned int intCount = 0;
    while (nanosleep(&ts, &ts) < 0 && errno == EINTR)
    {
        // Continue sleep if interrupted by signal.
        if (errno == EINTR)
        {
            intCount++;
        }
    }

    if (intCount > 0)
    {
        printf("Interrupt count %d\n", intCount);
    }
}
