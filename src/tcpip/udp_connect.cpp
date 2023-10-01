
/**
 * @file udp_connect.cpp
 * @brief UDP client example program, connect to server before read / write operations.
 * @author Shu, Zhong Hua
 * @date 2023-04-20
 */
#include <string>
#include <cstring>
#include <csignal>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fmt/format.h>
#include <fcntl.h>

#include "tcpip_func.h"

namespace {

void connectAlarm(const int signo)
{
    std::cout << fmt::format("Connection timeout, signo = {0}\n", signo);
}

int connectTimeout(const int sockfd, const sockaddr *const saptr, const socklen_t salen, const int nsec)
{
	tcpip::Sigfunc *sigfunc;
	int ret;

    // Start alarm timer to avoid connection exit after timeout.
	if ((sigfunc = tcpip::signalHandle(SIGALRM, connectAlarm)) == SIG_ERR)
    {
        std::cout << "Signal error\n";
    }

	if (::alarm((unsigned int)nsec) != 0)
    {
        std::cout << "Connection timeout: alarm was already set\n";
    }

    std::cout << "Start connect...\n";
	if ( (ret = ::connect(sockfd, saptr, salen)) < 0)
    {
        std::cout << "Connect error: " << ::strerror(errno) << "\n";
		::close(sockfd);
		if (EINTR == errno)
        {
            errno = ETIMEDOUT;
        }
	}

    // TCP / UDP connection function can't blocked if server not started?
    std::cout << "Socket connected: " << ret << "\n";

    // Turn off the alarm.
	::alarm(0);

    // Restore previous signal handler.
	if ((sigfunc = tcpip::signalHandle(SIGALRM, sigfunc)) == SIG_ERR)
    {
        std::cout << "Signal error\n";
    }

	return ret;
}


void setSocketOption([[maybe_unused]] const int sockfd)
{
#ifdef HAS_NON_BLOCK_OPTION
    int val;
    // Set socket option.
    if ((val = ::fcntl(sockfd, F_GETFL, 0)) < 0)
    {
        std::cout << "Fcntl get error\n";
    }

    if (::fcntl(sockfd, F_SETFL, val | O_NONBLOCK) < 0)
    {
        std::cout << "Fcntl set error\n";
    }
#endif

#ifdef HAS_SEND_TIMEOUT_OPTION
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    const socklen_t len = sizeof(timeout);
    if (::setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len) < -1)
    {
        std::cout << "setsockopt error\n";
    }
#endif
}

void dgCli(FILE * const fp, const int sockfd, const sockaddr * const pservaddr, const socklen_t servlen)
{
	int n;
	char sendline[tcpip::MAXLINE];
    char recvline[tcpip::MAXLINE + 1];
    const int CONN_TIMEOUT = 0;

    if (connectTimeout(sockfd, pservaddr, servlen, CONN_TIMEOUT) < 0)
    {
        std::cout << "Connect error\n";
    }

	while (::fgets(sendline, tcpip::MAXLINE, fp) != nullptr)
    {
        sendline[sizeof(sendline) - 1] = 0;
		if (::write(sockfd, sendline, ::strlen(sendline)) != (ssize_t)::strlen(sendline))
        {
            std::cout << "Write error\n";
            ::exit(1);
        }
		if ((n = (int)::read(sockfd, recvline, tcpip::MAXLINE)) == -1)
        {
            std::cout << "Read error: " << ::strerror(errno) << "\n";
            ::exit(1);
        }
		recvline[n] = 0;	/* null terminate */
		if (::fputs(recvline, stdout) == EOF)
        {
            std::cout << "Fputs error\n";
        }
	}
}

}
int main(int argc, char **argv)
{
    int sockfd;
    sockaddr_in servaddr;
    const int ARGC_NUM = 2;

	if (argc != ARGC_NUM)
    {
        std::cout << "usage: udpconnect <IPaddress>\n";

        ::exit(1);
    }

	if ((sockfd = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cout << "Socket error\n";
    }

    setSocketOption(sockfd);

	::memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = ::htons(tcpip::SERV_PORT);
	::inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    dgCli(stdin, sockfd, (sockaddr *)&servaddr, sizeof(servaddr));
}