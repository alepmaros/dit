#include "unp.h"
#include <time.h>

int main(int argc, char **argv)
{
    int                 listenfd, confd;
    struct_sockaddr_in  servaddr;
    char                buff(MAXLINE);
    time_t              ticks;

    if (argc != 2)
        err_quit("Usage: xxx");

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(atoi(argv[1]));

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    for(;;)
    {
        confd = Accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

        Close(connfd);
    }
    return 0;
}