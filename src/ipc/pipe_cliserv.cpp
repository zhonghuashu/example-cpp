
/**
 * @file pipe_cliserv.cpp
 * @brief IPC - Pipe client / server.
 * Client: Read file path from stdin, send to pipe 1.
 * Server: Read file path from pipe1, send file content to pipe 2.
 * Client: Read file content from pipe 2, write to stdout.
 *
 * @author Shu, Zhong Hua
 * @date 2023-05-21
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

#include <ipc_func.h>

int main(int argc, char **argv)
{
    int pipe1[2];
    int pipe2[2];
    pid_t childpid;

    if (::pipe(pipe1) < 0)
    {
        std::cout << "Pipe 1 error\n";
    }

    if (::pipe(pipe2) < 0)
    {
        std::cout << "Pipe 2 error\n";
    }

    if (0 == (childpid = ::fork()))
    {/* Child process. */

        // Close pipe 1 for write.
        ::close(pipe1[1]);
        // Close pipe 2 for read.
        ::close(pipe2[0]);

        ipc::server(pipe1[0], pipe2[1]);
        ::exit(0);
    }

    /* Parent class. */
    // Close pipe 1 for read.
    ::close(pipe1[0]);
    // Close pipe 2 for write.
    ::close(pipe2[1]);

    ipc::client(pipe2[0], pipe1[1]);
    if (::waitpid(childpid, nullptr, 0) == -1)
    {
        std::cout << "Waitpid error\n";
    }

    return EXIT_SUCCESS;
}