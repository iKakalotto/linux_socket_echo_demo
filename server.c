#include "echo.h"

int main()
{
    int server_fd, client_fd;
    int rv, fd;
    struct sockaddr_in server_addr, client_addr;
    char send_msg[MSG_LEN], recv_msg[MSG_LEN];
    fd_set set, tmp_set;
    socklen_t addr_len;

    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if_error(server_fd, "socket error!");

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);
    server_addr.sin_family = AF_INET;
    rv = bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if_error(rv, "bind error!");
    rv = listen(server_fd, 10);
    if_error(rv, "listen error!");

    FD_ZERO(&set);
    FD_SET(server_fd, &set);
    addr_len = sizeof(client_addr);
    while (true) {
        tmp_set = set;
        rv = select(FD_SETSIZE, &tmp_set, NULL, NULL, NULL);
        if_error(rv, "select error!");

        for (fd = 0; fd < FD_SETSIZE; fd++) {
            if (!FD_ISSET(fd, &tmp_set)) {
                continue;
            }

            if (fd == server_fd) {
                client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
                if_error(client_fd, "accept error!");
                printf("%s:%d has connect.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                FD_SET(client_fd, &set);
            } else {
                bzero(send_msg, MSG_LEN);
                bzero(recv_msg, MSG_LEN);

                rv = recv(fd, recv_msg, MSG_LEN, 0);
                if (rv == 0) {
                    printf("%s:%d has disconnect.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                    FD_CLR(fd, &set);
                    close(fd);
                }

                puts(recv_msg);
                rv = send(fd, recv_msg, MSG_LEN, 0);
            }
        }
    }

    close(server_fd);
    return EXIT_SUCCESS;
}