/**
 * @file tcpip_func.h
 * @brief TCP / IP common function.
 * @author Shu, Zhong Hua
 * @date 2023-04-20
 */
#ifndef TCPIP_FUNC_H
#define TCPIP_FUNC_H

#include <iostream>
namespace tcpip {

const int MAXLINE = 4096;
const int SERV_PORT = 9877;

/**
 * Sends the line to the remote peer.
 * @param fd File descriptor
 * @param vptr Write position
 * @param n Write bytes
 * @return
 */
ssize_t writeline(const int fd, const char *const vptr, const size_t n);

/**
 * Reads a line of text.
 * @param fd File descriptor
 * @param vptr Read position
 * @param maxlen Read bytes
 * @return
 */
ssize_t readline(const int fd, char *const vptr, const size_t maxlen);

/**
 * For signal handlers
 */
typedef	void Sigfunc(int);

/**
 * Signal handle via calling sigaction function.
 * @param signo Signal number
 * @param func Signal handle callback
 * @return Signal function pointer
 */
Sigfunc *signalHandle(const int signo, const Sigfunc * const func);

}

#endif

