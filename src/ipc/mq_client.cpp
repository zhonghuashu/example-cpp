/**
 * @file mq_client.cpp
 * @brief POSIX Message Queue client program.
 * @author Shu, Zhong Hua
 * @date 2023-05-26
 */
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <mqueue.h>

#include "ipc_func.h"

int main(int argc, char **argv)
{
    mqd_t mqd;
    mqd_t readMq;
    struct ipc::mymesg mesg;
    size_t len;
    pid_t pid;
    char *ptr;
    std::string queueName = CLI_MQ;
    ssize_t n;
    struct mq_attr attr;
    unsigned int priority;

    if ((mqd = ::mq_open(SERV_MQ, O_WRONLY, FILE_MODE, nullptr)) < 0)
    {
        std::cout << "Open server message queue failed: " << ::strerror(errno) << "\n";
    }

    pid = ::getpid();
    ::snprintf(mesg.mesgData, ipc::MAXMESGDATA, "%ld ", (long) pid);
	len = ::strlen(mesg.mesgData);
	ptr = mesg.mesgData + len;
    if ('\n' == mesg.mesgData[len - 1]) {  len--; }

    mesg.mesgLen = (long)len;
    mesg.mesgType = 1;

    if (nullptr == ::fgets(ptr, (int)(ipc::MAXMESGDATA - len), stdin))
    {
        std::cout << "Read pathname from stdin error\n";
    }
    len = ::strlen(mesg.mesgData);

    if (::mq_send(mqd, reinterpret_cast<char *>(&mesg), sizeof(mesg), (unsigned int)ipc::MessagePriority::HIGH) < 0)
    {
        std::cout << "Send message queue failed: " << ::strerror(errno) << "\n";
    }

    queueName += std::to_string(pid);
    if ((readMq = ::mq_open(queueName.c_str(), O_RDWR | O_CREAT, FILE_MODE, nullptr)) < 0)
    {
        std::cout << "Create client message queue failed: " << ::strerror(errno) << "\n";
    }

    if (::mq_getattr(readMq, &attr) < 0)
    {
        std::cout << "Get message queue attribute failed: " << ::strerror(errno) << "\n";
    }

    if ((n = ::mq_receive(readMq, reinterpret_cast<char *>(&mesg), (size_t)attr.mq_msgsize, &priority)) > 0)
    {
        std::cout << ">>>> Read message: [priority: " << priority << ", mesgType" << mesg.mesgType << ", mesgLen: " << mesg.mesgLen << "]\n";
        std::cout << mesg.mesgData;
    }

    if (::mq_close(mqd) < -1)
    {
        std::cout << "Close message queue failed: " << ::strerror(errno) << "\n";
    }

    if (::mq_close(readMq) < -1)
    {
        std::cout << "Close message queue failed: " << ::strerror(errno) << "\n";
    }

    if (::mq_unlink(queueName.c_str()) < -1)
    {
        std::cout << "Delete message queue failed: " << ::strerror(errno) << "\n";
    }

    return EXIT_SUCCESS;
}
