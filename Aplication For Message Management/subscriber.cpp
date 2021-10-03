#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include "helpers.h"

void usage(char *file)
{
    fprintf(stderr, "Usage: %s server_address server_port\n", file);
    exit(0);
}

int main(int argc, char *argv[])
{
    setvbuf(stdout,NULL,_IONBF,BUFSIZ);
    int sockfd,n,ret;
    struct sockaddr_in serv_addr;
    char buffer[BUFLEN];

    int bufferlenAux = sizeof(msg_t);
    char bufferAux[bufferlenAux];
    if (argc < 3) {
        usage(argv[0]);
    }

    if(strlen(argv[1]) > 10) {
        fprintf(stderr,"Client ID must have maximum 10 characters.\n");
        return 0;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    DIE(sockfd < 0, "socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[3]));
    ret = inet_aton(argv[2], &serv_addr.sin_addr);
    DIE(ret == 0, "inet_aton");

    ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    DIE(ret < 0, "connect");

    fd_set read_set, tmp_set;

    FD_ZERO(&read_set);
    FD_ZERO(&tmp_set);

    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(sockfd, &read_set);

    int maxfd = sockfd;
    bool ok = false;


    n = send(sockfd,argv[1],strlen(argv[1]) + 1,0);
    DIE(n < 0 , "send");


    memset(buffer, 0, BUFLEN);
    recv(sockfd, buffer, sizeof(buffer), 0);
    if(strncmp(buffer,"IDERROR",7) == 0) {
        close(sockfd);
        return 0;
    }
    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
    while(1) {
        tmp_set = read_set;

        int r = select(maxfd + 1, &tmp_set, NULL, NULL, NULL);
        DIE(r < 0, "Select");

        for (int i = 0; i <= maxfd; i++) {
            if (FD_ISSET(i, &tmp_set)) {
                if (i == STDIN_FILENO) {
                    memset(buffer, 0, BUFLEN);
                    fgets(buffer, BUFLEN - 1, stdin);
                    if (strncmp(buffer, "exit", 4) == 0) {
                        ok = true;
                        break;
                    }
                    char *copyBuffer = strdup(buffer);
                    char *token = strtok(copyBuffer," ");
                    
                    if(strncmp(token,"subscribe",9) == 0) {
                        token = strtok(NULL," ");
                        if(token == NULL) {
                            fprintf(stderr,"The token is null\n");
                            ok = true;
                            break;
                        }
                        token = strtok(NULL, " ");
                        if(token == NULL) {
                            fprintf(stderr,"SF is missing\n");
                            ok = true;
                            break;
                        }
                        int valueSF = atoi(token);
                        if(valueSF > 1) {
                            fprintf(stderr,"Value of sf is must be lower than 1.\n");
                            ok = true;
                            break;
                        }
                        printf("Subscribed to topic.\n");
                        n = send(sockfd,buffer,strlen(buffer),0);
                        DIE(n < 0 , "send");
                        free(copyBuffer);
                    }else if(strncmp(token,"unsubscribe",11) == 0) {
                        
                        printf("Unsubscribed from topic.\n");
                        n = send(sockfd,buffer,sizeof(buffer),0);
                        DIE(n < 0 , "send");
                        free(copyBuffer);
                    }else {
                        printf("The client accept only commands subscribe or unsubscribe.\n");
                    }
                } else {
                    memset(bufferAux,0,bufferlenAux);
                    int n = recv(i, bufferAux,sizeof(bufferlenAux), 0);
                    DIE(n < 0 , "recv");
                    if(strncmp(bufferAux,"OK",3) == 0){
                        break;
                    }
                    if (strncmp(bufferAux, "exit", 4) == 0) {
                        ok = true;
                        break;
                    }
                    printf("%s",bufferAux);
                }
            }
        }
        if(ok)
            break;
    }
    close(sockfd);
    return 0;
}
