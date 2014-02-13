#include "util.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        die("Parameters: <Server Port>");
    }

    int sock = setupServer(argv[1]);

    for (;;) {
        struct sockaddr_in clntAddr;
        socklen_t clntAddrLen = sizeof(clntAddr);

        int clntSock = accept(sock, (struct sockaddr *) &clntAddr, &clntAddrLen);
        if (clntSock < 0) {
            die("accept() failed");
        }

        char buffer[BUFSIZE];
        _recv(clntSock, buffer);
        _send(clntSock, "1");
    }

    return 0;
}
