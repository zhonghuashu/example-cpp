/**
 * @file tcp_client.cpp
 * @brief TCP client example program.
 * @author Shu, Zhong Hua
 * @date 2023-04-20
 */
#include <cstdio>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/socket.h>	/* basic socket definitions */
#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>	/* inet(3) functions */
#include <unistd.h>
#include <sys/uio.h>
#include <fmt/format.h>

#include "tcpip_func.h"

namespace {

void strCli(FILE *const fp, const int sockfd)
{
	char sendline[tcpip::MAXLINE], recvline[tcpip::MAXLINE];

	while ((::fgets(sendline, tcpip::MAXLINE, fp) != nullptr))
    {
        sendline[sizeof(sendline) - 1] = 0;
		tcpip::writeline(sockfd, &sendline[0], ::strlen(sendline));

		if (0 == tcpip::readline(sockfd, &recvline[0], tcpip::MAXLINE))
        {
            std::cout << "str_cli: server terminated prematurely\n";
            ::exit(1);
        }

		if (::fputs(recvline, stdout) < 0)
        {
            std::cout << "Fputs error\n";
        }
	}
}

}

int main(int argc, char **argv)
{
	int sockfd;
	sockaddr_in	servaddr;
    sockaddr_in	cliaddr;
    socklen_t len;
    const int ARGC_NUM = 2;
    char buff[tcpip::MAXLINE];

	if (argc != ARGC_NUM)
    {
        std::cout << "usage: tcpclient <IPaddress>\n";

        ::exit(1);
    }

	if ((sockfd = ::socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Socket error\n";
    }

	::memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = ::htons(tcpip::SERV_PORT);
	::inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	if (::connect(sockfd, (sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        std::cout << "Connect error: " << ::strerror(errno) << "\n";
    }

    len = sizeof(cliaddr);
    if (::getsockname(sockfd, (sockaddr *)&cliaddr, &len) < 0)
    {
        std::cout << "Getsockname error\n";
    }
    if (nullptr == ::inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)))
    {
        std::cout << "Inet_ntop error\n";
    }

    std::cout << fmt::format("Local address is {0}, port {1}\n", buff, ::ntohs(cliaddr.sin_port));

	strCli(stdin, sockfd);

	return EXIT_SUCCESS;
}
