
/**
 * @file udp_server.cpp
 * @brief UDP server example program.
 * @author Shu, Zhong Hua
 * @date 2023-04-20
 */
#include <string>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

#include "tcpip_func.h"

namespace {

void dgEcho(const int sockfd, sockaddr * const pcliaddr, const socklen_t clilen)
{
	ssize_t n;
	socklen_t len;
	char mesg[tcpip::MAXLINE];

	while (true)
    {
		len = clilen;
		if ((n = ::recvfrom(sockfd, mesg, tcpip::MAXLINE, 0, pcliaddr, &len)) < 0)
        {
            std::cout << "Receive from error\n";
            return;
        }

		if (::sendto(sockfd, mesg, (size_t)n, 0, pcliaddr, len) != n)
        {
            std::cout << "Send to error\n";
            return;
        }
	}
}

int joinMultiCast(const int sockfd, const sockaddr *const grp)
{
    struct ip_mreq mreq;

    ::memcpy(&mreq.imr_multiaddr, &((const struct sockaddr_in *) grp)->sin_addr, sizeof(struct in_addr));
    mreq.imr_interface.s_addr = ::htonl(INADDR_ANY);

    return (::setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)));
}

}

int main(int argc, char **argv)
{
    int sockfd;
    sockaddr_in servaddr;
    sockaddr_in cliaddr;
    sockaddr_in grpaddr;

    if ((sockfd = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cout << "Create socket error\n";
    }

    ::memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
    servaddr.sin_port = ::htons(tcpip::SERV_PORT);

    if (::bind(sockfd, (sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        std::cout << "Bind error\n";
    }

    // Join multi cast group address.
    ::memset(&grpaddr, 0, sizeof(grpaddr));
    grpaddr.sin_family = AF_INET;
    grpaddr.sin_addr.s_addr = ::inet_addr("224.0.0.1");
    if (joinMultiCast(sockfd, (sockaddr *)&grpaddr) < 0)
    {
        std::cout << "Join multi cast error\n";
    }

    dgEcho(sockfd, (sockaddr *)&cliaddr, sizeof(cliaddr));

    return EXIT_SUCCESS;
}

