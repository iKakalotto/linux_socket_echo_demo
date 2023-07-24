#include "echo.h"

int main()
{
    int client_fd;
    int rv;
    struct sockaddr_in addr_in;
    char send_msg[MSG_LEN];
    char recv_msg[MSG_LEN];

    client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if_error(rv, "socket error!");

    bzero(&addr_in, sizeof(addr_in));
    addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_in.sin_port = htons(8080);
    addr_in.sin_family = AF_INET;
    rv = connect(client_fd, (struct sockaddr*)&addr_in, sizeof(addr_in));
    if_error(rv, "connect error!");

    while (true) {
        bzero(send_msg, MSG_LEN);
        bzero(recv_msg, MSG_LEN);
        fprintf(stdout, ">>> ");
        fgets(send_msg, MSG_LEN, stdin);
        rv = send(client_fd, send_msg, MSG_LEN, 0);
        if_error(rv, "send msg error!");
        rv = recv(client_fd, recv_msg, MSG_LEN, 0);
        if_error(rv, "recv msg error!");
        puts(recv_msg);
    }

    close(client_fd);
    return EXIT_SUCCESS;
}
