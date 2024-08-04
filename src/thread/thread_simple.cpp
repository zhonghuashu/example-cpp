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

void *threadFunction(void *arg)
{
    pthread_setname_np(pthread_self(), "thread/1");

    std::string ret = "Thank you for the CPU time";
    std::cout << "Thread function is running. Argument was: " << (char *)arg << "\n";
    sleep(30);
    mMessage += " Bye!";

    pthread_exit((void *)ret.c_str());
}

}

int main()
{
    pthread_t aThread;
    void *threadResult;

    std::cout << "Starting thread...\n";
    if (pthread_create(&aThread, NULL, threadFunction, (void *)mMessage.c_str()) != 0)
    {
        std::cout << "Thread creation failed\n";

        return EXIT_FAILURE;
    }

    std::cout << "Waiting for thread to finish...\n";
    if (::pthread_join(aThread, &threadResult) != 0)
    {
        std::cout << "Thread join failed\n";

        return EXIT_FAILURE;
    }

    std::cout << "Thread joined, it returned: " <<  (char *)threadResult << "\n";
    std::cout << "Message now is: " << mMessage << "\n";

    return EXIT_SUCCESS;
}
