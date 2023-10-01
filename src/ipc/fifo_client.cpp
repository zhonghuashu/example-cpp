
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "ipc_func.h"
#include "tcpip_func.h"

int main(int argc, char **argv)
{
    int readfifo;
    int writefifo;
    size_t len;
    ssize_t n;
    char *ptr;
    std::string fifoname;
    char buff[ipc::MAXLINE];
    pid_t pid;

    pid = ::getpid();
    fifoname = "/tmp/fifo.";
    fifoname += std::to_string(pid);

    if ((::mkfifo(fifoname.c_str(), FILE_MODE) < 0) && (errno != EEXIST))
    {
        std::cout << "Can't create FIFO with our PID: " << fifoname << "\n";
    }

    ::snprintf(buff, sizeof(buff), "%ld ", (long) pid);
	len = ::strlen(buff);
	ptr = buff + len;

    if (nullptr == ::fgets(ptr, ipc::MAXLINE, stdin))
    {
        std::cout << "Read pathname from stdin error\n";
    }
    len = ::strlen(buff);

    if ((writefifo = ::open(SERV_FIFO, O_WRONLY, 0)) < 0)
    {
        std::cout << "Open server FIFO error\n";
    }
    if (::write(writefifo, buff, len) != (ssize_t)len)
    {
        std::cout << "Write PID / pathname to server FIFO error\n";
    }

    if ((readfifo = ::open(fifoname.c_str(), O_RDONLY, 0)) < 0)
    {
        std::cout << "Open client FIFO error\n";
    }
    while ((n = ::read(readfifo, buff, ipc::MAXLINE)) > 0)
    {
        if (::write(STDOUT_FILENO, buff, (size_t)n) != n)
        {
            std::cout << "Write IPC data to stdout error\n";
        }
    }

    return EXIT_SUCCESS;
}