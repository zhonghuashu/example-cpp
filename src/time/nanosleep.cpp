/**
 * @file nanosleep.cpp
 * @brief 精度是纳秒级, 暂停某个进程直到你规定的时间后恢复
 * @author Shu, Zhong Hua
 * @date 2023-10-14
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

namespace {
void nanoSleepTest()
{
    #define s  5          // 5s
    #define ns 999999999 // 大概是1s
    struct timespec s_sleep;
    struct timespec ns_sleep;
    s_sleep.tv_sec = s;
    s_sleep.tv_nsec = 0;
    ns_sleep.tv_sec = 0;
    ns_sleep.tv_nsec = ns;

    nanosleep(&s_sleep, nullptr);
    printf("nanosleep: 5 seconds passed...\n");

    nanosleep(&ns_sleep, nullptr);
    printf("nanosleep: 1 seconds passed...\n");
}

struct period_info {
    struct timespec next_period;
    long period_ns;
};

static void inc_period(struct period_info *pinfo)
{
    pinfo->next_period.tv_nsec += pinfo->period_ns;

    while (pinfo->next_period.tv_nsec >= 1000000000) {
        /* timespec nsec overflow */
        pinfo->next_period.tv_sec++;
        pinfo->next_period.tv_nsec -= 1000000000;
    }
}

static void periodic_task_init(struct period_info *pinfo)
{
    const unsigned int TIMEOUT = 500000;
    pinfo->period_ns = TIMEOUT;
    clock_gettime(CLOCK_MONOTONIC, &(pinfo->next_period));
}

static void wait_rest_of_period(struct period_info *pinfo)
{
    int result;
    struct timespec remain = {0, 0};
    inc_period(pinfo);
    result = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &pinfo->next_period, &remain);
    ::printf("clock_nanosleep(): ret = %d\n", result);
    ::printf("clock_nanosleep(): remain = [%ld, %ld]\n", remain.tv_sec, remain.tv_nsec);
}

void clockNanoSleepTest()
{
    struct period_info pinfo;
    periodic_task_init(&pinfo);
    ::sleep(1);
    wait_rest_of_period(&pinfo);
}

}

int main(int argc, char *argv[])
{
    nanoSleepTest();
    clockNanoSleepTest();
    return 0;
}
