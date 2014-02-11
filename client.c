#include "util.h"

#define POLLING_INTERVAL 1000

void send_request(server_t * server) {
    char buffer[BUFSIZE];
    bzero(buffer, BUFSIZE);

	int sock = setupClient(server->address, server->port);

	_send(sock, "test");
    _recv(sock, buffer);
    printf("%s\n", buffer);
}

void *start_requests(void * t) {
	server_t * server = t;
	struct timeval tv;

    while (1) {
    	tv.tv_sec = POLLING_INTERVAL;
	    tv.tv_usec = 0;

	    select(0, NULL, NULL, NULL, &tv);
        send_request(server);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
    	printf("%s\n", "Dying");
        die("Parameters: <Server Address> <Server Port>");
    }

    server_t * server = (server_t *) malloc(sizeof(server));
    server->address = argv[1];
    server->port = argv[2];

    pthread_t timer_thread;
    pthread_create(&timer_thread, NULL, start_requests, server);

    return 0;
}
