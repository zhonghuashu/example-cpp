/**
 * @file ipc_func.h
 * @brief IPC common function.
 * @author Shu, Zhong Hua
 * @date 2023-05-21
 */
#include <climits>
#include <semaphore.h>

#ifndef IPC_FUNC_H
#define IPC_FUNC_H

namespace ipc {
#define	SERV_FIFO   "/tmp/fifo.serv"
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
const int MAXLINE = 4096;

#define	SERV_MQ     "/mq.serv"
#define	CLI_MQ      "/mq."
const int MAXMESGDATA = 8192 - 2 * sizeof(long);

enum class MessagePriority
{
    LOW = 1,
    HIGH
};

struct mymesg
{
  long mesgLen;	/* #bytes in mesg_data, can be 0 */
  long mesgType;	/* message type, must be > 0 */
  char mesgData[MAXMESGDATA];
};

#define	MESGSIZE	256		/* max #bytes per message, incl. null at end */
#define	NMESG		 16		/* max #messages */

struct shmstruct
{		/* struct stored in shared memory */
    sem_t	mutex;			/* three Posix memory-based semaphores */
    sem_t	nempty;
    sem_t	nstored;
    int	nput;			/* index into msgoff[] for next put */
    long	noverflow;		/* #overflows by senders */
    sem_t	noverflowmutex;	/* mutex for noverflow counter */
    long	msgoff[NMESG];	/* offset in shared memory of each message */
    char	msgdata[NMESG * MESGSIZE];	/* the actual messages */
};


/**
 * Client function.
 * @param readfd Read file descriptor.
 * @param writefd Write file descriptor.
 */
void client(const int readfd, const int writefd);

/**
 * Server function.
 * @param readfd Read file descriptor.
 * @param writefd Write file descriptor.
 */
void server(const int readfd, const int writefd);

/**
 * Sleep for micro seconds using select()
 * @param nusecs micro seconds
 * @return success (0) or failed (-1)
 */
int sleep_us(const unsigned int nusecs);

}

#endif