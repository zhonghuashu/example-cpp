/**
 * @file fork.cpp
 * @brief Create new child process and wait child finished to avoid become zombie state.
 * @author Shu, Zhong Hua
 * @date 2023-06-03
 */

#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {

pid_t forkProcess()
{
    pid_t pid;
    std::string message;
    int n;

    ::printf("fork program starting\n");
    pid = ::fork();
    switch (pid)
    {
    case -1:
        ::perror("fork failed");
        exit(1);
    case 0:
        message = "This is the child";
        n = 5;
        break;
    default:
        message = "This is the parent";
        n = 3;
        break;
    }

    for (; n > 0; n--) {
        ::puts(message.c_str());
        ::sleep(1);
    }

    return pid;
}

void waitChildFinish(pid_t pid)
{
    if (pid)
    {
        int stat_val;
        pid_t child_pid;

        // Pause parent process until child process terminate.
        child_pid = ::wait(&stat_val);

        ::printf("Child has finished: PID = %d\n", child_pid);
        if (WIFEXITED(stat_val))    // Wait if exited.
        {
            ::printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        }
        else
        {
            ::printf("Child terminated abnormally\n");
        }
    }
}

void waitpidChildFinish(pid_t pid)
{
    if (pid)
    {
        int stat_val;
        pid_t child_pid;

        // Pause parent process until child process terminate.
        child_pid = ::waitpid(pid, &stat_val, 0);

        ::printf("Child has finished: PID = %d\n", child_pid);
        if (WIFEXITED(stat_val))    // Wait if exited.
        {
            ::printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        }
        else
        {
            ::printf("Child terminated abnormally\n");
        }
    }
}

}

int main()
{
    const int useWaitpid = 1;

    pid_t childpid = forkProcess();

    if (useWaitpid)
    {
        waitpidChildFinish(childpid);
    }
    else
    {
        waitChildFinish(childpid);
    }

    ::exit(0);
}
