
/**
 * @file ipc_func.cpp
 * @brief IPC common function.
 * @author Shu, Zhong Hua
 * @date 2023-05-21
 */
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

#include "ipc_func.h"


void ipc::client(const int readfd, const int writefd)
{
    size_t len;
    ssize_t n;
    char buff[ipc::MAXLINE];

    if (nullptr == ::fgets(buff, ipc::MAXLINE, stdin))
    {
        std::cout << "Fgets error\n";
    }

    buff[ipc::MAXLINE - 1] = '\n';
    len = ::strlen(buff);

    if (::write(writefd, buff, len - 1) != (ssize_t)len)
    {
        std::cout << "Write error\n";
    }

    while ((n = ::read(readfd, buff, ipc::MAXLINE)) > 0)
    {
        if (::write(STDOUT_FILENO, buff, (size_t)n) != n)
        {
            std::cout << "Write error\n";
        }
    }
}

void ipc::server(const int readfd, const int writefd)
{
    int fd;
    ssize_t n;
    char buff[ipc::MAXLINE + 1];

    if (0 == (n = ::read(readfd, buff, ipc::MAXLINE)))
    {
        std::cout << "End of file while reading pathname.\n";
    }

    buff[n] = '\0';
    if ((fd = ::open(buff, O_RDONLY)) < 0)
    {
        std::cout << "Can't open file: " << ::strerror(errno) << "\n";
        if (::write(writefd, buff, ::strlen(buff)) != n)
        {
            std::cout << "Write error\n";
        }
    }
    else
    {
        while ((n = ::read(fd, buff, ipc::MAXLINE)) > 0)
        {
            if (::write(writefd, buff, (size_t)n) != n)
            {
                std::cout << "Write error\n";
            }
        }
    }
}

int ipc::sleep_us(const unsigned int nusecs)
{
	struct timeval	tval;

	if (0 == nusecs) { return(0); }

	while (true)
    {
		tval.tv_sec = nusecs / 1000000;
		tval.tv_usec = nusecs % 1000000;
		if (0 == ::select(0, nullptr, nullptr, nullptr, &tval))
        {
            return(0);
        }

		/*
		 * Note than on an interrupted system call there's not
		 * much we can do, since the timeval{} isn't updated with the time
		 * remaining.  We could obtain the clock time before the call, and
		 * then obtain the clock time here, subtracting them to determine
		 * how long select() blocked before it was interrupted, but that
		 * seems like too much work :-)
		 */
		if (errno != EINTR)
        {
            return(-1);
        }

		/* else go around again */
	}
}