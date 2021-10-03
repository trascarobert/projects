#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include <iostream>
#include <string>

using namespace std;
char *compute_get_request(char *host, char *url, char *query_params,
                            string cookies,string token)
{
    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));

    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }

    compute_message(message, line);

    memset(line,0,LINELEN);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    
    if (cookies.compare("") != 0) {
        char auxialiryBuffer[cookies.length() + 1];
        strcpy(auxialiryBuffer,cookies.c_str());
        memset(line,0,LINELEN);
        sprintf(line, "Cookie: %s", auxialiryBuffer);
        compute_message(message, line);
    }
    if (token.compare("") != 0) {
        char auxialiryBuffer[token.length() + 1];
        strcpy(auxialiryBuffer,token.c_str());
        compute_message(message,auxialiryBuffer);
    }
    compute_message(message, "");
    return message;
}
char *compute_delete(char *host, char *url, char *query_params,
                          string cookies,string token)
{
    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));

    if (query_params != NULL) {
        sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "DELETE %s HTTP/1.1", url);
    }

    compute_message(message, line);

    memset(line,0,LINELEN);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    
    if (cookies.compare("") != 0) {
        char auxialiryBuffer[cookies.length() + 1];
        strcpy(auxialiryBuffer,cookies.c_str());
        memset(line,0,LINELEN);
        sprintf(line, "Cookie: %s", auxialiryBuffer);
        compute_message(message, line);
    }
    if (token.compare("") != 0) {
        char auxialiryBuffer[token.length() + 1];
        strcpy(auxialiryBuffer,token.c_str());
        compute_message(message,auxialiryBuffer);
    }
    compute_message(message, "");
    return message;
}
char *compute_post_request(char *host, char *url, char* content_type, string body_data,
                           string cookies,string token)
{
    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    sprintf(line, "Host: %s", host);
    compute_message(message, line);
   sprintf(line, "Content-Type: %s", content_type);
   compute_message(message, line);

   int len = body_data.length();
   sprintf(line, "Content-Length: %d", len);
   compute_message(message, line);
    if (token.compare("") != 0) {
        char auxialiryBuffer[token.length() + 1];
        strcpy(auxialiryBuffer,token.c_str());
        compute_message(message,auxialiryBuffer);
    }
    if (cookies.compare("") != 0)  {
        char auxialiryBuffer[cookies.length() + 1];
        strcpy(auxialiryBuffer,cookies.c_str());
        memset(line,0,LINELEN);
        sprintf(line, "Cookie: %s", auxialiryBuffer);
        compute_message(message, line);
    }
    compute_message(message, "");
    memset(line, 0, LINELEN);
    compute_message(message, body_data.c_str());

    free(line);
    return message;
}
