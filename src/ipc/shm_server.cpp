/**
 * @file shm_server.cpp
 * @brief Consumer with POSIX shared memory, like syslog daemon process.
 * usaage: <program> shm.serv
 * - Server create shared memory object.
 * - Client process put message in shm.
 * - Server print out message in shm.
 * POSIX shared memory object stored in /dev/shm filesystem.
 * https://www.man7.org/linux/man-pages/man3/shm_open.3.html
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
    int fd, index, lastnoverflow, temp;
    long offset;
    struct ipc::shmstruct *ptr;
    size_t shmLen = sizeof(struct ipc::shmstruct);

    if (argc != 2)
    {
        std::cout << fmt::format(FMT_STRING("usage: {0} <name>\n"), argv[0]);

        return EXIT_FAILURE;
    }

    /* create shm, set its size, map it, close descriptor */
    ::shm_unlink(argv[1]);		/* OK if this fails */

    if ((fd = ::shm_open(argv[1], O_RDWR | O_CREAT | O_EXCL, FILE_MODE)) < 0)
    {
        std::cout << "Open shared memory failed: " << ::strerror(errno) << "\n";
    }
    ptr = (ipc::shmstruct *)::mmap(nullptr, shmLen, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ::ftruncate(fd, (long)shmLen);
    ::close(fd);

    /* initialize the array of offsets */
    for (index = 0; index < NMESG; index++)
    {
        ptr->msgoff[index] = index * MESGSIZE;
    }

    /* 4initialize the semaphores in shared memory */
    ::sem_init(&ptr->mutex, 1, 1);
    ::sem_init(&ptr->nempty, 1, NMESG);
    ::sem_init(&ptr->nstored, 1, 0);
    ::sem_init(&ptr->noverflowmutex, 1, 1);

    /* this program is the consumer */
    index = 0;
    lastnoverflow = 0;
    while (true)
    {
        ::sem_wait(&ptr->nstored);
        ::sem_wait(&ptr->mutex);
        offset = ptr->msgoff[index];
        ::printf("index = %d: %s\n", index, &ptr->msgdata[offset]);
        index++;
        if (index >= NMESG)
        {
            index = 0;				/* circular buffer */
        }

        ::sem_post(&ptr->mutex);
        ::sem_post(&ptr->nempty);

        ::sem_wait(&ptr->noverflowmutex);
        temp = (int)ptr->noverflow;		/* don't printf while mutex held */
        ::sem_post(&ptr->noverflowmutex);
        if (temp != lastnoverflow)
        {
            ::printf("noverflow = %d\n", temp);
            lastnoverflow = temp;
        }
    }

    return EXIT_SUCCESS;
}
