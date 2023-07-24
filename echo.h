#ifndef _ECHO_H
#define _ECHO_H

#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define MSG_LEN 128

void if_error(int rv, char* msg)
{
    if (rv < 0) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

#endif
