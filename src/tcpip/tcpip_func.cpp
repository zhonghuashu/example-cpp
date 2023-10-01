/**
 * @file tcpip_func.cpp
 * @brief TCP IP common function.
 * @author Shu, Zhong Hua
 * @date 2023-04-20
 */
#include <csignal>
#include <unistd.h>

#include "tcpip_func.h"

namespace {

ssize_t read_cnt;
char *read_ptr;
char read_buf[tcpip::MAXLINE];

ssize_t myRead(const int fd, char * const ptr)
{
    while (read_cnt <= 0)
    {
        if ((read_cnt = ::read(fd, read_buf, sizeof(read_buf))) < 0)
        {
            if (EINTR == errno)
            {
                continue;
            }
            else
            {
                std::cout << "Read error\n";
                return -1;
            }
        }
        else if (0 == read_cnt)
        {
            return 0;
        }
        else
        {
            read_ptr = read_buf;
        }
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return 1;
}

}

ssize_t tcpip::writeline(const int fd, const char *const vptr, const size_t n)
{
    size_t		nleft;
    ssize_t		nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0)
    {
        if ((nwritten = ::write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && (EINTR == errno))
            {
                // And call write() again.
                std::cout << "Write error: " << errno << "\n";
                nwritten = 0;
            }
            else
            {
                return -1;
            }
        }

        nleft -= (size_t)nwritten;
        ptr += nwritten;
    }

    return (ssize_t)n;
}

ssize_t tcpip::readline(const int fd, char *const vptr, const size_t maxlen)
{
    ssize_t	n, rc;
    char c;
    char *ptr;

    ptr = vptr;
    for (n = 1; n < (ssize_t)maxlen; ++n)
    {
        if (1 == (rc = myRead(fd, &c)))
        {
            *ptr++ = c;
            if ('\n' == c) { break; }	/* newline is stored, like fgets() */
        }
        else if (0 == rc)
        {
            *ptr = 0;
            return (n - 1);	/* EOF, n - 1 bytes were read */
        }
        else
        {
            return -1;		/* error, errno set by read() */
        }
    }

    *ptr = 0;	/* null terminate like fgets() */

    return n;
}

tcpip::Sigfunc *tcpip::signalHandle(const int signo, const tcpip::Sigfunc * const func)
{
	struct sigaction act, oact;

	act.sa_handler = func;
	::sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (SIGALRM == signo)
    {
#ifdef	SA_INTERRUPT
		act.sa_flags |= (unsigned int)SA_INTERRUPT;	/* SunOS 4.x */
#endif
	} else
    {
#ifdef	SA_RESTART
		act.sa_flags |= (unsigned int)SA_RESTART;		/* SVR4, 44BSD */
#endif
	}
	if (::sigaction(signo, &act, &oact) < 0)
    {
        return(SIG_ERR);
    }

	return(oact.sa_handler);
}
