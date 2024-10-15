/**
 * @file thread_simple.cpp
 * @brief Share variables with original thread, gets new thread to return a result to the original thread.
 *
 * @author Shu, Zhong Hua
 * @date 2023-05-27
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <linux/prctl.h>
#include <unistd.h>
#include <pthread.h>

namespace {

std::string mMessage = "Hello World";
bool mThreadFinished = false;
void *threadFunction(void *arg)
{
    pthread_setname_np(pthread_self(), "thread/1");

    std::string ret = "Thank you for the CPU time";
    std::cout << "Thread function is running. Argument was: " << (char *)arg << "\n";
    sleep(30);
    mMessage += " Bye!";
    mThreadFinished = true;
    pthread_exit((void *)ret.c_str());
}

void setRtPriorityMain(const int prio)
{
    struct sched_param param;
    const pid_t pid = ::getpid();

    param.sched_priority = prio;
    ::sched_setscheduler(pid, SCHED_RR, &param);
    ::pthread_setschedparam(::pthread_self(), SCHED_RR, &param);
}

}

int main()
{
    pthread_t aThread;

    // Main process / child thread priority are changed.
    setRtPriorityMain(40);
    std::cout << "Starting thread in detach state...\n";

    pthread_attr_t threadAttr;
    if (::pthread_attr_init(&threadAttr) != 0)
    {
        ::perror("Thread attribute init failed");
        return EXIT_FAILURE;
    }
    ::pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);

    if (pthread_create(&aThread, &threadAttr, threadFunction, (void *)mMessage.c_str()) != 0)
    {
        std::cout << "Thread creation failed\n";

        return EXIT_FAILURE;
    }

    std::cout << "Waiting for thread to finish...\n";
    while (!mThreadFinished)
    {
        static int count;
        // Wait until child thread finished.
        ::sleep(1);
        std::cout << "Waiting seconds: " << count++ << "\n";
    }

    std::cout << "Thread finished, it returned\n";
    std::cout << "Message now is: " << mMessage << "\n";

    return EXIT_SUCCESS;
}
