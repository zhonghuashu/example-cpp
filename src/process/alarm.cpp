/**
 * @file alarm.cpp
 * @brief the first function, ding, simulates an alarm clock.
 * child process to wait for five seconds to send SIGALARM signal to it's parent.
 * @author Shu, Zhong Hua
 * @date 2023-06-03
 */
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include <unistd.h>

namespace {
static int alarmFired = 0;

void ding(int sig)
{
    ::printf("I got signal %d\n", sig);
    alarmFired = 1;
}

}

int main()
{
    pid_t pid;

    ::printf("alarm application starting\n");

    pid = ::fork();
    switch (pid)
    {
    case -1:
        /* Failure */
        ::perror("fork failed");
        ::exit(1);
    case 0:
        /* child */
        ::sleep(5);
        // Send alarm signal to parent process.
        ::kill(getppid(), SIGALRM);
        ::exit(0);
    default:
        /* parent */
        break;
    }

    ::printf("Waiting for alarm to go off\n");
    ::signal(SIGALRM, ding);

    // Suspend process until signal.
    ::pause();
    if (alarmFired)
    {
        ::printf("Ding!\n");
    }

    ::printf("done\n");
    ::exit(0);
}
