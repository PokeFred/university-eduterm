#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "shared_memory.h"
#include "dataframe.h"

int main(int argc, char **argv) {
    const char *address = argv[1];
    const char *port = "49152";
    struct addrinfo hints;
    struct addrinfo *result, *current_result;

    if (argc < 2 || strlen(argv[1]) < 1) {
        errx(EXIT_FAILURE, "Missing address as argument");
    }

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    int error = getaddrinfo(address, port, &hints, &result);
    if (error != 0) {
        err(EXIT_FAILURE, "getaddrinfo: %s\n", gai_strerror(error));
    }

    int socket_fd;
    for (current_result = result; current_result != NULL; current_result = current_result->ai_next) {
        socket_fd = socket(current_result->ai_family, current_result->ai_socktype, current_result->ai_protocol);
        if (socket_fd == -1) continue;
        if (connect(socket_fd, current_result->ai_addr, current_result->ai_addrlen) != -1) break;
        close(socket_fd);
    }
    if (current_result == NULL) errx(EXIT_FAILURE, "Could not connect");
    freeaddrinfo(result);

    // TODO Shared Memory auslesen, frame(s) befüllen und absenden
    page_t ttt = {
        "TTT1",
        "TTT2",
        "TTT3",
        "TTT4"
    };
    dataframe frame = {
        1, ttt
    };

    if (write(socket_fd, &frame, sizeof(frame)) != sizeof(frame)) {
        err(EXIT_FAILURE, "partial/failed write\n");
    }

    close(socket_fd);

    return EXIT_SUCCESS;
}
