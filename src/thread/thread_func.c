/**
 * @file thread_sample.c
 * @brief Example test code for Linux thread usage.
 * @author Shu, Zhong Hua
 * @date 2022-08-15
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "thread_func.h"

static const int DELAY_COUT = 500000000;
static int thread_finished = 0;

static void *thread1(void *pp)
{
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);
    switch (policy)
    {
    case SCHED_OTHER:
        printf("SCHED_OTHER 1\n");
        break;
    case SCHED_RR:
        printf("SCHED_RR 1 \n");
        break;
    case SCHED_FIFO:
        printf("SCHED_FIFO 1\n");
        break;
    default:
        break;
    }

    while (thread_finished != 0)
    {
        for (int i = 1; i < DELAY_COUT; ++i)
        {
        }
        printf("Pthread 1\n");
    }

    pthread_exit("Thank you for the CPU time");
}

static void *thread2(void *pp)
{
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);
    switch (policy)
    {
    case SCHED_OTHER:
        printf("SCHED_OTHER 2\n");
        break;
    case SCHED_RR:
        printf("SCHED_RR 2 \n");
        break;
    case SCHED_FIFO:
        printf("SCHED_FIFO 2\n");
        break;
    default:
        break;
    }
    while (thread_finished != 0)
    {
        for (int i = 1; i < DELAY_COUT; ++i)
        {
        }
        printf("Pthread 2\n");
    }

    pthread_exit("Thank you for the CPU time");
}

static void *thread3(void *pp)
{
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);
    switch (policy)
    {
    case SCHED_OTHER:
        printf("SCHED_OTHER 3\n");
        break;
    case SCHED_RR:
        printf("SCHED_RR 3 \n");
        break;
    case SCHED_FIFO:
        printf("SCHED_FIFO 3\n");
        break;
    default:
        break;
    }
    while (thread_finished != 0)
    {
        for (int i = 1; i < DELAY_COUT; ++i)
        {
        }
        printf("Pthread 3\n");
    }

    pthread_exit("Thank you for the CPU time");
}

static void checkSchedPriority()
{
    int min_priority;
    int max_priority;

    min_priority = sched_get_priority_min(SCHED_OTHER);
    max_priority = sched_get_priority_max(SCHED_OTHER);

    printf("min priority [SCHED_OTHER] = %d\n", min_priority);
    printf("max priority [SCHED_OTHER] = %d\n", max_priority);

    min_priority = sched_get_priority_min(SCHED_FIFO);
    max_priority = sched_get_priority_max(SCHED_FIFO);

    printf("min priority [SCHED_FIFO] = %d\n", min_priority);
    printf("max priority [SCHED_FIFO] = %d\n", max_priority);

    min_priority = sched_get_priority_min(SCHED_RR);
    max_priority = sched_get_priority_max(SCHED_RR);

    printf("min priority [SCHED_RR] = %d\n", min_priority);
    printf("max priority [SCHED_RR] = %d\n", max_priority);
}

static void setCurrentThread()
{
    struct sched_param param;
    pid_t pid = getpid();

    param.sched_priority = sched_get_priority_max(SCHED_RR);
    sched_setscheduler(pid, SCHED_RR, &param);
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
}

bool thread_main()
{
    int uid;
    uid = getuid();
    if (uid == 0)
    {
        printf("The current user is root\n");
    }
    else
    {
        printf("The current user is not root\n");
    }

    pthread_t ppid1, ppid2, ppid3;

    struct sched_param param1;
    struct sched_param param2;
    struct sched_param param3;
    enum Priority
    {
        PRIORITY_THREAD_1 = 10,
        PRIORITY_THREAD_2 = 20,
        PRIORITY_THREAD_3 = 30
    };

    pthread_attr_t attr1, attr2, attr3;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    checkSchedPriority();
    setCurrentThread();

    param1.sched_priority = PRIORITY_THREAD_1;
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr1, SCHED_RR);
    if (0 != pthread_attr_setschedparam(&attr1, &param1))
    {
        printf("setschedpolicy attr1 NG! \n");
    }

    param2.sched_priority = PRIORITY_THREAD_2;
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    pthread_attr_setschedparam(&attr2, &param2);
    if (0 != pthread_attr_setschedparam(&attr2, &param2))
    {
        printf("setschedpolicy attr2 NG! \n");
    }

    param3.sched_priority = PRIORITY_THREAD_3;
    pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr3, SCHED_RR);
    pthread_attr_setschedparam(&attr3, &param3);
    if (0 != pthread_attr_setschedparam(&attr3, &param3))
    {
        printf("setschedpolicy attr3 NG! \n");
    }

    pthread_create(&ppid1, &attr1, thread1, NULL);

    pthread_create(&ppid2, &attr2, thread2, NULL);

    pthread_create(&ppid3, &attr3, thread3, NULL);

    pthread_join(ppid1, NULL);
    pthread_join(ppid2, NULL);
    pthread_join(ppid3, NULL);

    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);
    pthread_attr_destroy(&attr3);

    return true;
}