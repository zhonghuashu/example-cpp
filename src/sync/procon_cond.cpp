/**
 * @file cond_procon.cpp
 * @brief Produce / consume and waiting for condition signal.
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

/* globals shared by threads */
int		nitems;				/* read-only by producer and consumer */
int		buff[MAXNITEMS];
struct {
    pthread_mutex_t	mutex;
    int				nput;	/* next index to store */
    int				nval;	/* next value to store */
} put = { PTHREAD_MUTEX_INITIALIZER };

struct {
    pthread_mutex_t	mutex;
    pthread_cond_t	cond;
    int				nready;	/* number ready for consumer */
} nready = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER };

void *produce(void *arg)
{
	while (true)
    {
        int dosignal;

		::pthread_mutex_lock(&put.mutex);
		if (put.nput >= nitems)
        {
			::pthread_mutex_unlock(&put.mutex);
			return(nullptr);		/* array is full, we're done */
		}
		buff[put.nput] = put.nval;
		put.nput++;
		put.nval++;
		::pthread_mutex_unlock(&put.mutex);

		::pthread_mutex_lock(&nready.mutex);
        dosignal = (0 == nready.nready);
		nready.nready++;
		::pthread_mutex_unlock(&nready.mutex);

		if (dosignal)
        {
			::pthread_cond_signal(&nready.cond);
        }

		*((int *) arg) += 1;
	}
}

void *consume(void *arg)
{
	for (int i = 0; i < nitems; i++)
    {
		::pthread_mutex_lock(&nready.mutex);
		while (0 == nready.nready)
        {
            ::pthread_cond_wait(&nready.cond, &nready.mutex);
        }

		nready.nready--;
		::pthread_mutex_unlock(&nready.mutex);

		if (buff[i] != i)
        {
            ::printf("buff[%d] = %d\n", i, buff[i]);
        }
	}

    std::cout << fmt::format("put[nput={0}, nval={1}]\n", put.nput, put.nval);
	return(nullptr);
}

}


int main(int argc, char **argv)
{
	int			i, nthreads, count[MAXNTHREADS];
	pthread_t	tid_produce[MAXNTHREADS], tid_consume;

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
	::pthread_create(&tid_consume, nullptr, consume, nullptr);

	/* wait for all producers and the consumer */
	for (i = 0; i < nthreads; i++)
    {
		::pthread_join(tid_produce[i], nullptr);
		::printf("count[%d] = %d\n", i, count[i]);
	}
	::pthread_join(tid_consume, nullptr);

	return EXIT_SUCCESS;
}
