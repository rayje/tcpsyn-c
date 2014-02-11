#ifndef __MY_UTIL_H
#define __MY_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>

#define BUFSIZE 65535
#define MAXPENDING 5

typedef struct  {
	char *address;
	char *port;
} server_t;

/**
 * Print the message and exit with return code 1.
 */
void die(const char * msg);

/**
 * Send a message using the provided socket handle.
 */
int _send(int sock, char * buff);

/**
 * Receive a message of the provided socket handle.
 */
int _recv(int sock, char * buff);

/** 
 * Setup a socket servet using the provided port.
 */
int setupServer(char * port);

/**
 * Setup a socket client.
 */
int setupClient(char * servIP, char * port);

#endif