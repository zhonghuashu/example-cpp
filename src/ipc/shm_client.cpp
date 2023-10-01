/**
 * @file shm_client.cpp
 * @brief Produce with POSIX shared memory.
 * usage: <program> shm.serv 50 0
 * @author Shu, Zhong Hua
 * @date 2023-05-28
 */
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <fmt/format.h>

#include "ipc_func.h"

int main(int argc, char **argv)
{
    int fd, nloop, nusec;
    pid_t pid;
    char mesg[MESGSIZE];
    long offset;
    struct ipc::shmstruct *ptr;
    size_t shmLen = sizeof(struct ipc::shmstruct);

    if (argc != 4)
    {
        std::cout << fmt::format(FMT_STRING("usage: {0} <name> <#loops> <#usec>\n"), argv[0]);

        return EXIT_FAILURE;
    }

    nloop = std::stoi(argv[2]);
    nusec = std::stoi(argv[3]);

    /* open and map shared memory that server must create */
    if ((fd = ::shm_open(argv[1], O_RDWR, FILE_MODE)) < 0)
    {
        std::cout << "Open shared memory failed: " << ::strerror(errno) << "\n";
    }
    ptr = (ipc::shmstruct *)::mmap(nullptr, shmLen, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ::close(fd);

    pid = ::getpid();
    for (int i = 0; i < nloop; i++)
    {
        ipc::sleep_us((unsigned int)nusec);
        ::snprintf(mesg, MESGSIZE, "pid %ld: message %d", (long)pid, i);

        if (::sem_trywait(&ptr->nempty) == -1)
        {
            if (EAGAIN == errno)
            {
                ::sem_wait(&ptr->noverflowmutex);
                ptr->noverflow++;
                ::sem_post(&ptr->noverflowmutex);
                continue;
            }
            else
            {
                std::cout << "em_trywait error\n";
            }
        }
        ::sem_wait(&ptr->mutex);
        offset = ptr->msgoff[ptr->nput];
        ptr->nput++;
        if (ptr->nput >= NMESG)
        {
            ptr->nput = 0;		/* circular buffer */
        }

        ::sem_post(&ptr->mutex);
        ::strcpy(&ptr->msgdata[offset], mesg);
        ::sem_post(&ptr->nstored);
    }

    return EXIT_SUCCESS;
}
