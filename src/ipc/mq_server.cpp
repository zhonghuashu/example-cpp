/**
 * @file mq_server.cpp
 * @brief POSIX Message Queue server program.
 * The message queue are created in virtual file system, can be mounted in file system using commands:
 * # mkdir /dev/mqueue
 * # mount -t mqueue none /dev/mqueue
 * # umount /dev/mqueue
 * See https://man7.org/linux/man-pages/man7/mq_overview.7.html
 * @author Shu, Zhong Hua
 * @date 2023-05-23
 */
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>

#include "ipc_func.h"

int main(int argc, char **argv)
{
    mqd_t mqd;
    struct mq_attr attr;
    ssize_t n;
    struct ipc::mymesg mesg;
    unsigned int priority;

    if ((mqd = ::mq_open(SERV_MQ, O_RDWR | O_CREAT, FILE_MODE, nullptr)) < 0)
    {
        std::cout << "Create server message queue failed: " << ::strerror(errno) << "\n";
    }

    if (::mq_getattr(mqd, &attr) < 0)
    {
        std::cout << "Get message queue attribute failed: " << ::strerror(errno) << "\n";
    }

    while ((n = ::mq_receive(mqd, reinterpret_cast<char *>(&mesg), (size_t)attr.mq_msgsize, &priority)) > 0)
    {
        char *ptr;
        pid_t pid;
        std::string queueName;
        mqd_t writeMq;
        int fd;
        char * buff = mesg.mesgData;
        int len;

        buff[ipc::MAXMESGDATA - 1] = '\0';
        len = ::strlen(buff);
        if ('\n' == buff[len - 1]) { len--; }
        buff[len] = '\0';

        std::cout << ">>>> Read message: [priority: " << priority << ", mesgType: " << mesg.mesgType << ", mesgLen: " << mesg.mesgLen << ", mesgData: " << mesg.mesgData << "]\n";

        if (nullptr == (ptr = ::strchr(buff, ' ')))
        {
			std::cout << "Bogus request:" << buff << "\n";
			continue;
		}

        *ptr++ = 0;
        pid = (pid_t)std::stol(buff);

        queueName = CLI_MQ;
        queueName += std::to_string(pid);

        if ((writeMq = ::mq_open(queueName.c_str(), O_WRONLY, FILE_MODE, nullptr)) < 0)
        {
            std::cout << "Open client message queue failed: " << ::strerror(errno) << "\n";
        }

        if ((fd = ::open(ptr, O_RDONLY)) < 0)
        {
			::snprintf(buff, ipc::MAXMESGDATA, "%s: can't open, %s\n", queueName.c_str(), ::strerror(errno));

            if (::mq_send(writeMq, reinterpret_cast<char *>(&mesg), sizeof(mesg), (unsigned int)ipc::MessagePriority::LOW) < 0)
            {
                std::cout << "Send message queue failed: " << ::strerror(errno) << "\n";
            }
        }
        else
        {
            if ((n = ::read(fd, buff, ipc::MAXMESGDATA)) > 0)
            {
                if (::mq_send(writeMq, reinterpret_cast<char *>(&mesg), sizeof(mesg), (unsigned int)ipc::MessagePriority::LOW) < 0)
                {
                    std::cout << "Send message queue failed: " << ::strerror(errno) << "\n";
                }
            }
            if (::close(fd) < 0)
            {
                std::cout << "Close opened file error\n";
            }
        }

        if (::mq_close(writeMq) < -1)
        {
            std::cout << "Close message queue failed: " << ::strerror(errno) << "\n";
        }
    }

    if (::mq_close(mqd) < -1)
    {
        std::cout << "Close message queue failed: " << ::strerror(errno) << "\n";
    }

    if (::mq_unlink(SERV_MQ) < -1)
    {
        std::cout << "Delete message queue failed: " << ::strerror(errno) << "\n";
    }

    return EXIT_SUCCESS;
}
