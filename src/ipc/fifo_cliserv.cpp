/**
 * @file fifo_cliserv.cpp
 * @brief IPC - Named pipe (FIFO) client / server.
 * Client: Read file path from stdin, send to FIFO1.
 * Server: Read file path from FIFO1, send file content to FIFO2.
 * Client: Read file content from FIFO2, write to stdout.
 *
 * @author Shu, Zhong Hua
 * @date 2023-05-21
 */
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "ipc_func.h"

namespace {
#define	FIFO1   "/tmp/fifo.1"
#define	FIFO2   "/tmp/fifo.2"

}

int main(int argc, char **argv)
{
    int readfd;
    int writefd;
    pid_t childpid;

    if ((::mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
    {
        std::cout << "Can't create fifo: " << FIFO1 << "\n";
    }

    if ((::mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST))
    {
        std::cout << "Can't create fifo: " << FIFO2 << "\n";
    }

    if (0 == (childpid = ::fork()))
    {/* Child process. */

        if (-1 == (readfd = ::open(FIFO1, O_RDONLY, 0)))
        {
            std::cout << "Open fifo error: " << FIFO1 << "\n";
        }
        if (-1 == (writefd = ::open(FIFO2, O_WRONLY, 0)))
        {
            std::cout << "Open fifo error: " << FIFO2 << "\n";
        }

        ipc::server(readfd, writefd);
        ::exit(0);
    }

    /* Parent class. */
    if (-1 == (writefd = ::open(FIFO1, O_WRONLY, 0)))
    {
        std::cout << "Open fifo error: " << FIFO1 << "\n";
    }
    if (-1 == (readfd = ::open(FIFO2, O_RDONLY, 0)))
    {
        std::cout << "Open fifo error: " << FIFO2 << "\n";
    }

    ipc::client(readfd, writefd);

    if (::waitpid(childpid, nullptr, 0) == -1)
    {
        std::cout << "Waitpid error\n";
    }

    if (::unlink(FIFO1) == -1)
    {
        std::cout << "Unlink error\n";
    }

    if (::unlink(FIFO2) == -1)
    {
        std::cout << "Unlink error\n";
    }

    return EXIT_SUCCESS;
}