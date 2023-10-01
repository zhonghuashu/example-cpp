/**
 * @file tcp_server.cpp
 * @brief TCP server example program.
 * @author Shu, Zhong Hua
 * @date 2023-04-20
 */

#include <ctime>
#include <cstring>
#include <csignal>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>	/* basic socket definitions */
#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/uio.h>
#include <fmt/format.h>
#include <sys/wait.h>

#include "tcpip_func.h"

namespace {
const int LISTENQ = 1024;	/* 2nd argument to listen() */

void strEcho(const int sockfd)
{
    ssize_t n;
    char buf[tcpip::MAXLINE];
    time_t ticks;

    // Daytime server
    ticks = ::time(nullptr);
    ::ctime_r(&ticks, buf);
    const std::string timeStr = fmt::format("Connected at: {0}", buf);
    tcpip::writeline(sockfd, timeStr.c_str(), timeStr.length());

    while ((n = ::read(sockfd, buf, tcpip::MAXLINE)) > 0)
    {
        if (tcpip::writeline(sockfd, &buf[0], (size_t)n) != n)
        {
            std::cout << "Writen error\n";
        }
    }
}

void sigChld(const int signo)
{
	pid_t pid;
	int stat;

	pid = ::wait(&stat);
	std::cout << fmt::format("Child {0} terminated, signo = {1}\n", pid, signo);
}

}

int main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    sockaddr_in cliaddr, servaddr;
    tcpip::Sigfunc *sigfunc;
    const int on = 1;

    if ((listenfd = ::socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Create socket error\n";
    }

    if (::setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        std::cout << "Set socketopt error\n";
    }

    ::memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
    servaddr.sin_port = ::htons(tcpip::SERV_PORT);


    if (::bind(listenfd, (sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        std::cout << "Bind error\n";
    }

    if (::listen(listenfd, LISTENQ) < 0)
    {
        std::cout << "Listen error\n";
    }

	if ( (sigfunc = tcpip::signalHandle(SIGCHLD, sigChld)) == SIG_ERR)
    {
        std::cout << "Signal error\n";
    }

    while (true)
    {
        char buff[tcpip::MAXLINE];
        clilen = sizeof(cliaddr);

        if ((connfd = ::accept(listenfd, (sockaddr *)&cliaddr, &clilen)) < 0)
        {
            std::cout << "Accept error\n";
        }

        if (nullptr == ::inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)))
        {
            std::cout << "Inet_ntop error\n";
        }

        std::cout << fmt::format("Connction from {0}, port {1}\n", buff, ::ntohs(cliaddr.sin_port));

        if (0 == (childpid = ::fork()))
        {/* child process */

            // Close listening socket.
            ::close(listenfd);

            // Process the request.
            strEcho(connfd);
            ::exit(0);
        }

        // Parent closes connected socket.
        ::close(connfd);
    }

    return EXIT_SUCCESS;
}
