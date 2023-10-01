
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
    int dummyfd;
    char buff[ipc::MAXLINE];

	ssize_t	n;

	if ((::mkfifo(SERV_FIFO, FILE_MODE) < 0) && (errno != EEXIST))
    {
        std::cout << "Can't create server fifo: " << SERV_FIFO << "\n";
    }

	if (-1 == (readfifo = ::open(SERV_FIFO, O_RDONLY, 0)))
    {
        std::cout << "Open server fifo for read error: " << SERV_FIFO << "\n";
    }

    if (-1 == (dummyfd = ::open(SERV_FIFO, O_WRONLY, 0)))
    {
        std::cout << "Open server fifo for write error: " << SERV_FIFO << "\n";
    }

    while ((n = tcpip::readline(readfifo, buff, ipc::MAXLINE)) > 0)
    {
        int writefifo;
        int fd;
	    char *ptr;
        std::string fifoname;
        pid_t pid;

        if ('\n' == buff[n -1]) { n--; }
        buff[n] = '\0';
        if (nullptr == (ptr = ::strchr(buff, ' ')))
        {
			std::cout << "Bogus request:" << buff << "\n";
			continue;
		}

        *ptr++ = 0;
        pid = (pid_t)std::stol(buff);

        fifoname = "/tmp/fifo.";
        fifoname += std::to_string(pid);

        if ((writefifo = ::open(fifoname.c_str(), O_WRONLY, 0)) < 0)
        {
            std::cout << "Can't open client FIFO: " << fifoname << "\n";
        }

        if ((fd = ::open(ptr, O_RDONLY)) < 0)
        {
			::snprintf(buff + n, sizeof(buff) - (unsigned long)n, ": can't open, %s\n", ::strerror(errno));
            n = (ssize_t)::strlen(ptr);

            if (::write(writefifo, ptr, (size_t)n) != n)
            {
                std::cout << "Write error to client FIFO error\n";
            }
        }
        else
        {
            while ((n = ::read(fd, buff, ipc::MAXLINE)) > 0)
            {
                if (::write(writefifo, buff, (size_t)n) != n)
                {
                    std::cout << "Write file to client FIFO error\n";
                }
            }

            if (::close(fd) < 0)
            {
                std::cout << "Close opened file error\n";
            }
        }

        if (::close(writefifo) < 0)
        {
            std::cout << "Close client FIFO error\n";
        }
    }

    return EXIT_SUCCESS;
}
