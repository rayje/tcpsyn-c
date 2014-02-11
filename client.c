#include "util.h"
#include "time_util.h"

struct server_t {
	char *address.
	char *port
};

void *send_request() {
    char buffer[BUFSIZE];
    bzero(buffer, BUFSIZE);

	int sock = setupClient(argv[1], argv[2]);

	_send(sock, "test");
    _recv(sock, buffer);
    printf("%s\n", buffer);
}

void *start_requests() {
    while (1) {
        run_timer(POLLING_INTERVAL, send_request);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
    	printf("%s\n", "Dying");
        die("Parameters: <Server Address> <Server Port>");
    }

    struct server_t * server = (struct server_t *) malloc(sizeof(server));
    server->address = argv[1];
    server->port = argv[2];

    pthread_t timer_thread;
    int status = pthread_create(&timer_thread, NULL, start_requests, server);

    return 0;
}
