#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include "helpers.h"
#include <map>
#include <valarray>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <sstream>

void usage(char *file)
{
    fprintf(stderr, "Usage: %s server_port\n", file);
    exit(0);
}
int main(int argc, char *argv[])
{
    setvbuf(stdout,NULL,_IONBF,BUFSIZ);
    int sockfd, newsockfd, portno;
    int udpfd;
    char buffer[BUFLEN];
    struct sockaddr_in serv_addr, cli_addr;
    int n, i, ret;
    socklen_t clilen;

    msg_t udpContent;
    std::map<int,std::string> clients;
    std::set<std::string> offline;
    std::set<std::pair<std::string,std::string>> s;
    std::unordered_map <std::string,std::vector<std::string>> memorateMessage;
    std::unordered_map <std::string,std::vector<std::string>> sendMessageOffline;
    fd_set read_fds;	
    fd_set tmp_fds;		
    int fdmax;			
    if (argc < 2) {
        usage(argv[0]);
    }

    FD_ZERO(&read_fds);
    FD_ZERO(&tmp_fds);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    DIE(sockfd < 0, "socket");

    udpfd = socket(PF_INET,SOCK_DGRAM,0);
    DIE(udpfd < 0,"udp");

    portno = atoi(argv[1]);
    DIE(portno == 0, "atoi");

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(portno);
    cli_addr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));
    DIE(ret < 0, "bind");

    ret = bind(udpfd, (struct sockaddr *) &cli_addr, sizeof(struct sockaddr));
    DIE(ret < 0,"bind");

    ret = listen(sockfd, MAX_CLIENTS);
    DIE(ret < 0, "listen");

    
    FD_SET(sockfd, &read_fds);
    FD_SET(udpfd,&read_fds);
    FD_SET(STDIN_FILENO,&read_fds);

    fdmax = std::max(sockfd,udpfd);

    bool ok = false;
    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));
    std::vector<std::pair<std::string,int>> vectorOfSubjects;
    while (1) {
        tmp_fds = read_fds;

        ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
        DIE(ret < 0, "select");

        for (i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &tmp_fds)) {
                if (i == STDIN_FILENO) {
                    memset(buffer, 0, BUFLEN);
                    fgets(buffer, BUFLEN - 1, stdin);
                   
                    if (strncmp(buffer, "exit", 4) == 0) {
                        ok = true;
                        for (int j = 3; j <= fdmax; j++) {
                            if (j != sockfd && FD_ISSET(j, &read_fds)) {
                                send(j, buffer, strlen(buffer) + 1, 0);
                                close(j);
                                FD_CLR(j, &read_fds);
                            }
                        }
                        break;
                    } else {
                        printf("The server can only receive `exit`!\n");
                    }
                }else if(i == udpfd) {
                    
                    int bufferAuxLen = sizeof(msg_t);
                    char bufferAux[bufferAuxLen];
                    memset(bufferAux,0,bufferAuxLen);
                    n = recv(i,bufferAux,sizeof(bufferAux),0);
                    DIE(n < 0, "recv");

                    memset(udpContent.topic_name,0,51);
                    strncpy(udpContent.topic_name,bufferAux,50);
                    udpContent.type = (uint8_t)bufferAux[50];
                    memset(udpContent.data,0,1501);
                    int size = 0;
                    for(int k = 51 ; k < 1551 ; k++){
                        udpContent.data[size] = bufferAux[k];
                        size++;
                    }
                    switch(udpContent.type) {
                       
                        case 0: {
                            // INT
                            long long valueContent = ntohl(*(uint32_t *)(udpContent.data + 1));
                            if (udpContent.data[0] == 1) {
                                valueContent *= -1;
                            }
                            std::string stringToSend;
                            stringToSend += inet_ntoa(cli_addr.sin_addr);
                            stringToSend += ":";
                            stringToSend += std::to_string(htons(cli_addr.sin_port));
                            stringToSend += " - ";
                            stringToSend += udpContent.topic_name;
                            stringToSend += " - ";
                            stringToSend += "INT";
                            stringToSend += " - ";
                            stringToSend += std::to_string(valueContent);
                            stringToSend += '\n';
                            memset(bufferAux,0,bufferAuxLen);
                            strcpy(bufferAux,stringToSend.c_str());
                            
                            for (std::pair<int, std::string> element : clients) {
                                for (std::pair<std::string, std::string> elementFromSet : s) {
                                    if (element.second == elementFromSet.first) {
                                        if (elementFromSet.second == udpContent.topic_name) {
                                            send(element.first, bufferAux, strlen(bufferAux), 0);
                                        }
                                    }
                                }
                            }
                            for(std::string offlineID : offline) {
                                for(std::pair<std::string,std::vector<std::string>> element : memorateMessage) {
                                    if(element.first == offlineID) {
                                        for(std::string contentElem : element.second) {
                                            if(contentElem == udpContent.topic_name) {
                                                sendMessageOffline[element.first].push_back(stringToSend);
                                            }
                                        }
                                    }
                                }
                            }
                        } break;
                        case 1: {
                            // SHORT_REAL
                            float valueContent = ntohs(*(uint16_t*)udpContent.data);
                            valueContent /= 100;
                            sprintf(udpContent.data,"%.2f",valueContent);
                            std::string stringToSend;
                            stringToSend += inet_ntoa(cli_addr.sin_addr);
                            stringToSend += ":";
                            stringToSend += std::to_string(htons(cli_addr.sin_port));
                            stringToSend += " - ";
                            stringToSend += udpContent.topic_name;
                            stringToSend += " - ";
                            stringToSend += "SHORT_REAL";
                            stringToSend += " - ";
                            stringToSend += udpContent.data;
                            stringToSend += '\n';
                            memset(bufferAux,0,bufferAuxLen);
                            strcpy(bufferAux,stringToSend.c_str());
                            for(std::pair<int,std::string> element : clients) {
                                for (std::pair<std::string, std::string> elementFromSet : s) {
                                    if(element.second == elementFromSet.first) {
                                        if(elementFromSet.second == udpContent.topic_name) {
                                            send(element.first,bufferAux,strlen(bufferAux),0);
                                        }
                                    }
                                }
                            }
                            for(std::string offlineID : offline) {
                                for(std::pair<std::string,std::vector<std::string>> element : memorateMessage) {
                                    if(element.first == offlineID) {
                                        for(std::string contentElem : element.second) {
                                            if(contentElem == udpContent.topic_name) {
                                                sendMessageOffline[element.first].push_back(stringToSend);
                                            }
                                        }
                                    }
                                }
                            }
                        }break;
                        case 2:{
                            // FLOAT
                            double valueContent = ntohl(*(uint32_t*)(udpContent.data + 1));
                            valueContent /= pow(10,udpContent.data[5]);
                            if (udpContent.data[0] == 1) {
                                valueContent *= -1;
                            }
                            sprintf(udpContent.data,"%lf", valueContent);
                            std::string stringToSend;
                            stringToSend += inet_ntoa(cli_addr.sin_addr);
                            stringToSend += ":";
                            stringToSend += std::to_string(htons(cli_addr.sin_port));
                            stringToSend += " - ";
                            stringToSend += udpContent.topic_name;
                            stringToSend += " - ";
                            stringToSend += "FLOAT";
                            stringToSend += " - ";
                            stringToSend += udpContent.data;
                            stringToSend += '\n';
                            memset(bufferAux,0,bufferAuxLen);
                            strcpy(bufferAux,stringToSend.c_str());
                            for(std::pair<int,std::string> element : clients) {
                                for (std::pair<std::string, std::string> elementFromSet : s) {
                                    if(element.second == elementFromSet.first) {
                                        if(elementFromSet.second == udpContent.topic_name) {
                                            send(element.first,bufferAux,strlen(bufferAux),0);
                                        }
                                    }
                                }
                            }
                            for(std::string offlineID : offline) {
                                for(std::pair<std::string,std::vector<std::string>> element : memorateMessage) {
                                    if(element.first == offlineID) {
                                        for(std::string contentElem : element.second) {
                                            if(contentElem == udpContent.topic_name) {
                                                sendMessageOffline[element.first].push_back(stringToSend);
                                            }
                                        }
                                    }
                                }
                            }
                        }break;
                        case 3: {
                            // STRING
                            char *valueFromBuffer = strdup(udpContent.data);
                            std::string stringToSend;
                            stringToSend += inet_ntoa(cli_addr.sin_addr);
                            stringToSend += ":";
                            stringToSend += std::to_string(htons(cli_addr.sin_port));
                            stringToSend += " - ";
                            stringToSend += udpContent.topic_name;
                            stringToSend += " - ";
                            stringToSend += "STRING";
                            stringToSend += " - ";
                            stringToSend += valueFromBuffer;
                            stringToSend += '\n';
                            memset(bufferAux,0,bufferAuxLen);
                            strcpy(bufferAux,stringToSend.c_str());
                            for(std::pair<int,std::string> element : clients) {
                                for (std::pair<std::string, std::string> elementFromSet : s) {
                                    if(element.second == elementFromSet.first) {
                                        if(elementFromSet.second == udpContent.topic_name) {
                                            send(element.first,bufferAux,strlen(bufferAux),0);
                                        }
                                    }
                                }
                            }
                            for(std::string offlineID : offline) {
                                for(std::pair<std::string,std::vector<std::string>> element : memorateMessage) {
                                    if(element.first == offlineID) {
                                        for(std::string contentElem : element.second) {
                                            if(contentElem == udpContent.topic_name) {
                                                sendMessageOffline[element.first].push_back(stringToSend);
                                            }
                                        }
                                    }
                                }
                            }
                        }break;
                        default:
                            printf("Value of data type is not right.\n");
                    }
                }else if (i == sockfd) {
                    int bufferAuxLen = sizeof(msg_t);
                    char bufferAux[bufferAuxLen];
                    clilen = sizeof(cli_addr);
                    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                    DIE(newsockfd < 0, "accept");
                    FD_SET(newsockfd, &read_fds);
                    if (newsockfd > fdmax) {
                        fdmax = newsockfd;
                    }
                    char id_client[BUFLEN];
                    recv(newsockfd,id_client,BUFLEN - 1,0);
                    int alreadyIDConnected = 0;
                    for(std::pair<int,std::string> element : clients) {
                        if(element.second == id_client) {
                            alreadyIDConnected = 1;
                        }
                    }
                    if(alreadyIDConnected == 0) {
                        clients.insert(std::pair<int, std::string>(newsockfd, id_client));
                        printf("New client %s connected from %s:%d.\n",id_client,
                               inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
                        send(newsockfd, "OK", 3, 0);
                        
                        for(std::pair<std::string,std::vector<std::string>> elem : sendMessageOffline) {
                            if (elem.first == id_client) {
                                for (std::string element : elem.second) {
                                    memset(bufferAux,0,bufferAuxLen);
                                    strcpy(bufferAux,element.c_str());
                                    send(newsockfd,bufferAux,strlen(bufferAux),0);
                                }
                            }
                        }
                        std::string remove;
                        std::stringstream ss;
                        ss << id_client;
                        ss >> remove;
                        offline.erase(remove);
                        sendMessageOffline.erase(remove);
                    }else {
                        printf("Client %s already connected.\n",id_client);
                        send(newsockfd,"IDERROR",7,0);
                        close(newsockfd);
                        FD_CLR(newsockfd,&read_fds);
                    }
                } else {
                    memset(buffer,0,BUFLEN);
                    n = recv(i,buffer,sizeof(buffer),0);
                    DIE(n < 0, "recv");
                    if(n == 0) {
                        int deleteFromMap;
                        
                        for(std::pair<int,std::string> element : clients) {
                            if(element.first == i) {
                                printf("Client %s disconnected.\n",element.second.c_str());
                                offline.insert(std::string(element.second));
                                deleteFromMap = element.first;
                                close(i);
                                FD_CLR(i,&read_fds);
                            }
                        }
                        auto it = clients.find(deleteFromMap);
                        clients.erase(it);
                    }else {
                        char *copyBuffer = strdup(buffer);
                        char *token = strtok(copyBuffer," ");
                        
                        if(strncmp(token,"subscribe",9) == 0) {
                            char *content = strtok(NULL," ");
                            token = strtok(NULL, " ");
                            int valueSF = atoi(token);
                            for(std::pair<int,std::string> element : clients) {
                                if(element.first == i){
                                    s.insert(std::make_pair(element.second,content));
                                    if(valueSF == 1) {
                                        memorateMessage[element.second].push_back(content);
                                    }
                                }
                            }
                        }else if(strncmp(token,"unsubscribe",11) == 0){
                            char *content = strtok(NULL," ");
                            std::pair<std::string,std::string> deleteFromSet;
                            for(std::pair<int,std::string> element : clients) {
                                if(element.first == i){
                                    for(std::pair<std::string,std::string> elementFromSet : s) {
                                        if(elementFromSet.second == content && element.second == elementFromSet.first){
                                            deleteFromSet = std::make_pair(elementFromSet.first,elementFromSet.second);
                                        }
                                    }
                                }
                            }
                            s.erase(deleteFromSet);
                        }
                        free(copyBuffer);
                    }
                }
            }
        }
        if(ok)
            break;
    }

    close(sockfd);
    close(udpfd);
    return 0;
}
