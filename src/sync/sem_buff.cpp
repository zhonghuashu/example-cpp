/**
 * @file sem_buff.cpp
 * @brief Read / write file using POSIX semaphore.
 * Produce thread: Read files into multiple buffer.
 * Consume thread: Write buffer to stdout while produce thread is running.
 * @author Shu, Zhong Hua
 * @date 2023-05-27
 */
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <fmt/format.h>

namespace {

#define	NBUFF	 8
#define BUFFSIZE 512
struct
{	/* data shared by producer and consumer */
    struct
    {
        char data[BUFFSIZE];			/* a buffer */
        ssize_t	n;						/* count of #bytes in the buffer */
    } buff[NBUFF];					    /* NBUFF of these buffers/counts */
    sem_t mutex, nempty, nstored;		/* semaphores, not pointers */
} shared;

int	 mFd;							    /* input file to copy to stdout */

void *produce(void *arg)
{
	int i = 0;

	while (true)
    {
		::sem_wait(&shared.nempty);	/* wait for at least 1 empty slot */
		::sem_wait(&shared.mutex);
	    /* 4critical region */
		::sem_post(&shared.mutex);

		if ((shared.buff[i].n = ::read(mFd, shared.buff[i].data, BUFFSIZE)) < 0)
        {
            std::cout << "Read file failed\n";
        }

		if (0 == shared.buff[i].n)
        {
			if (::sem_post(&shared.nstored) < 0)	/* 1 more stored item */
            {
                std::cout << "Post stored semaphore failed\n";
            }

			return(nullptr);
		}
        else
        {
            std::cout << fmt::format(FMT_STRING(">>> Produce: Write buffer[{0}] = len[{1}]\n"), i, shared.buff[i].n);
        }

        i++;
		if (i >= NBUFF)
        {
            i = 0;					/* circular buffer */
        }

		::sem_post(&shared.nstored);	/* 1 more stored item */
	}
}

void *consume(void *arg)
{
	int i = 0;

	while (true)
    {
		::sem_wait(&shared.nstored);		/* wait for at least 1 stored item */
		::sem_wait(&shared.mutex);
		/* critical region */
		::sem_post(&shared.mutex);

		if (0 == shared.buff[i].n)
        {
            return(nullptr);
        }

        std::cout << fmt::format(FMT_STRING("\n>>> Consume: Read buffer[{0}] = len[{1}]\n"), i, shared.buff[i].n);
		::write(STDOUT_FILENO, shared.buff[i].data, (size_t)shared.buff[i].n);
        i++;
		if (i >= NBUFF)
        {
            i = 0;					/* circular buffer */
        }

		::sem_post(&shared.nempty);		/* 1 more empty slot */
	}
}

}

int main(int argc, char **argv)
{
	pthread_t	tid_produce, tid_consume;

	if (argc != 2)
    {
        std::cout << fmt::format(FMT_STRING("usage: {0} <pathname>\n"), argv[0]);

        return EXIT_FAILURE;
    }

	if ((mFd = ::open(argv[1], O_RDONLY)) < 0)
    {
        std::cout << "Open file failed: " << argv[1] << "\n";
    }

	/* initialize three semaphores */
	if (::sem_init(&shared.mutex, 0, 1) < 0)
    {
        std::cout << "Initialize mutex semaphore failed\n";
    }
	if (::sem_init(&shared.nempty, 0, NBUFF) < 0)
    {
        std::cout << "Initialize empty semaphore failed\n";
    }
	if (::sem_init(&shared.nstored, 0, 0) < 0)
    {
        std::cout << "Initialize stored semaphore failed\n";
    }

	if (::pthread_create(&tid_produce, nullptr, produce, nullptr) != 0) /* reader thread */
    {
        std::cout << "Create reader thread failed\n";
    }
	if (::pthread_create(&tid_consume, nullptr, consume, nullptr) != 0) /* writer thread */
    {
        std::cout << "Create writer thread failed\n";
    }

	if (::pthread_join(tid_produce, nullptr) != 0)
    {
        std::cout << "Wait produce thread failed\n";
    }
	if (::pthread_join(tid_consume, nullptr) != 0)
    {
        std::cout << "Wait consume thread failed\n";
    }

	if (::sem_destroy(&shared.mutex) < 0)
    {
        std::cout << "Destroy multex semaphore failed\n";
    }
	if (::sem_destroy(&shared.nempty) < 0)
    {
        std::cout << "Destroy empty semaphore failed\n";
    }
	if (::sem_destroy(&shared.nstored) < 0)
    {
        std::cout << "Destroy stored semaphore failed\n";
    }

	return EXIT_SUCCESS;
}
