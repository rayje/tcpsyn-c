#include "util.h"

void die(const char * msg) {
    perror(msg);
    exit(1);
}

int _send(int sock, char * buff) {
    int bytes = send(sock, buff, strlen(buff), 0);
    if (bytes < 0) {
        printf("send() failed: %d\n", bytes);
    }

    return bytes;
}

int _recv(int sock, char * buff) {
    unsigned int nBytes = 0;
    bzero(buff, BUFSIZE);

    nBytes = recv(sock, buff, BUFSIZE, 0);
    if (nBytes < 0) {
        die("recv() failed");
    } else if (nBytes == 0) {
        die("recv() failed: connection failed prematurely");
    }

    return nBytes;
}

int setupServer(char * port) {
    in_port_t servPort = atoi(port);

    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        die("socket() failed");
    }

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(servPort);

    int yes = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 ) {
        perror("setsockopt");
    }

    if (bind(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        die("bind() failed");
    }

    if (listen(sock, MAXPENDING) < 0) {
        die("listen() failed");
    }

    return sock;
}



int setupClient(char * servIP, char * port) {
    in_port_t servPort = atoi(port);

    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        die("socket() failed");
    }

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
    if (rtnVal == 0) {
        die("inet_pton() failed: invalid address string");
    } else if (rtnVal < 0) {
        die("inet_pton() failed");
    }

    servAddr.sin_port = htons(servPort);

    struct timeval before;
    struct timeval after;

	gettimeofday(&before, NULL);
    int rc = connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr));
    gettimeofday(&after, NULL);

    double t1=before.tv_sec+(before.tv_usec/1000000.0);
    double t2=after.tv_sec+(after.tv_usec/1000000.0);

    printf("\n%.6lf seconds elapsed\n", t2-t1);


    if (rc < 0) {
        die("connect() failed");
    }

    return sock;
}