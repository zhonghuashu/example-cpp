/**
 * @file mutex_procon.cpp
 * @brief Produce / consume using mutex
 * usage: <program> 1000000 5
 * @author Shu, Zhong Hua
 * @date 2023-05-27
 */
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <fmt/format.h>

namespace {

#define	MAXNITEMS 		1000000
#define	MAXNTHREADS			100
#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

int nitems;			/* read-only by producer and consumer */
struct
{
    pthread_mutex_t	mutex;
    int	buff[MAXNITEMS];
    int	nput;
    int	nval;
} shared = { PTHREAD_MUTEX_INITIALIZER };

void *produce(void *arg)
{
	while (true)
    {
		::pthread_mutex_lock(&shared.mutex);
		if (shared.nput >= nitems)
        {
			::pthread_mutex_unlock(&shared.mutex);
			return(nullptr);		/* array is full, we're done */
		}
		shared.buff[shared.nput] = shared.nval;
		shared.nput++;
		shared.nval++;
		::pthread_mutex_unlock(&shared.mutex);
		*((int *) arg) += 1;
	}
}

void *consume(void *arg)
{
	for (int i = 0; i < nitems; i++)
    {
		if (shared.buff[i] != i)
        {
			::printf("buff[%d] = %d\n", i, shared.buff[i]);
        }
	}

    std::cout << fmt::format("shared[nput={0}, nval={1}]\n", shared.nput, shared.nval);

	return(nullptr);
}

}

int main(int argc, char **argv)
{
	int i, nthreads, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
    {
        std::cout << fmt::format(FMT_STRING("usage: {0} <#items> <#threads>\n"), argv[0]);
    }

	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

	for (i = 0; i < nthreads; i++)
    {
		count[i] = 0;
		::pthread_create(&tid_produce[i], nullptr, produce, &count[i]);
	}

    /* wait for all the producer threads */
	for (i = 0; i < nthreads; i++)
    {
		::pthread_join(tid_produce[i], nullptr);
		::printf("count[%d] = %d\n", i, count[i]);
	}

	/* start, then wait for the consumer thread */
	::pthread_create(&tid_consume, nullptr, consume, nullptr);
	::pthread_join(tid_consume, nullptr);

	return EXIT_SUCCESS;
}
