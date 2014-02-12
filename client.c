#include "util.h"

#define POLLING_INTERVAL 10

void send_request(server_t * server) {
	struct timeval before;
    struct timeval after;
    char buffer[BUFSIZE];
    bzero(buffer, BUFSIZE);

	int sock = setupClient(server->address, server->port);

	gettimeofday(&before, NULL);
	_send(sock, "1");
    _recv(sock, buffer);
    gettimeofday(&after, NULL);

    int t1=(before.tv_sec*1000000)+before.tv_usec;
    int t2=(after.tv_sec*1000000)+after.tv_usec;

    printf(",%d\n", t2-t1);
}

void start_requests(server_t * server) {
	struct timeval tv;

    while (1) {
    	tv.tv_sec = POLLING_INTERVAL;
	    tv.tv_usec = 0;

	    select(0, NULL, NULL, NULL, &tv);
        send_request(server);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        die("Parameters: <Server Address> <Server Port>");
    }

    server_t * server = (server_t *) malloc(sizeof(server));
    server->address = argv[1];
    server->port = argv[2];

    start_requests(server);

    return 0;
}
