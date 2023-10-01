
/**
 * @file udp_client.cpp
 * @brief UDP client example program.
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

void dgCli(FILE * const fp, const int sockfd, const sockaddr * const pservaddr, const socklen_t servlen)
{
	int n;
	char sendline[tcpip::MAXLINE];
    char recvline[tcpip::MAXLINE + 1];
    char buff[tcpip::MAXLINE];
    sockaddr_in replyAddr;
    socklen_t len = servlen;

	while (::fgets(sendline, tcpip::MAXLINE, fp) != nullptr)
    {
        sendline[sizeof(sendline) - 1] = 0;
		if (::sendto(sockfd, sendline, ::strlen(sendline), 0, pservaddr, servlen) != (ssize_t)::strlen(sendline))
        {
            std::cout << "Send to error\n";
            ::exit(1);
        }
		if ((n = (int)::recvfrom(sockfd, recvline, tcpip::MAXLINE, 0, (sockaddr *)&replyAddr, &len)) == -1)
        {
            std::cout << "Receive from error: " << ::strerror(errno) << "\n";
            ::exit(1);
        }

        if (nullptr == ::inet_ntop(AF_INET, &replyAddr.sin_addr, buff, sizeof(buff)))
        {
            std::cout << "Inet_ntop error\n";
        }

        std::cout << "From " << buff << ": ";

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
        std::cout << "usage: udpclient <IPaddress>\n";
        std::cout << "       udpclient 127.0.0.1\n";
        std::cout << "       udpclient 224.0.0.1\n";

        ::exit(1);
    }

	if ((sockfd = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cout << "Socket error\n";
    }

	::memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = ::htons(tcpip::SERV_PORT);
	::inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    dgCli(stdin, sockfd, (sockaddr *)&servaddr, sizeof(servaddr));
}