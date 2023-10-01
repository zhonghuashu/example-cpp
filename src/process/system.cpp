/**
 * @file system.cpp
 * @brief Create and run new process.
 * exec function is more efficient than system(), because original process will not be running.
 * @author Shu, Zhong Hua
 * @date 2023-06-02
 */
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

namespace {

void runSystem()
{
    ::printf("Running ps with system\n");
    ::system("ps ax &");
    ::printf("Done\n");
}

void runExec()
{
    ::printf("Running ls with execlp\n");
    ::execl("/bin/ls", "ls", "-lt", nullptr);
    ::printf("Done\n");
}

}
int main()
{
    runSystem();
    runExec();
    ::exit(0);
}
