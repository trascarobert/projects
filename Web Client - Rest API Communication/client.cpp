#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <iostream>
#include <string>
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;
    string username,password;
    string command;
    string id;
    string sesionCookie = "";
    string token = "";
    string title,author,genre,publisher,page_count;
    while(1) {
       
        cin>>command;
        cin.ignore();
        if(command.compare("register") == 0) {
            
            cout << "username=";
            getline(cin,username);
            cout << "password=";
            getline(cin,password);
            json detailsLogin;
            detailsLogin["username"] = username;
            detailsLogin["password"] = password;

            string containsLoginData = detailsLogin.dump();

            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            message = compute_post_request("34.118.48.238", "/api/v1/tema/auth/register", "application/json",
                                           containsLoginData, "","");

            puts(message);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            puts(response);
            close_connection(sockfd);
        }else if(command.compare("login") == 0){
            
            token = "";
            cout << "username=";
            getline(cin,username);
            cout << "password=";
            getline(cin,password);

            json detailsLogin;
            detailsLogin["username"] = username;
            detailsLogin["password"] = password;

            string containsLoginData = detailsLogin.dump();

            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            message = compute_post_request("34.118.48.238", "/api/v1/tema/auth/login", "application/json",
                                           containsLoginData, "","");
            puts(message);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            puts(response);
            
            string responseString(response);
            size_t posStart = responseString.find("connect.sid");
            size_t posStop = responseString.find("Path");
            if(posStart != -1)
                sesionCookie = responseString.substr(posStart,posStop - posStart - 1);
            close_connection(sockfd);
        }else if(command.compare("enter_library") == 0){
            
                sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
                message = compute_get_request("34.118.48.238","/api/v1/tema/library/access",NULL,sesionCookie,"");
                puts(message);
                send_to_server(sockfd, message);
                response = receive_from_server(sockfd);
                puts(response);
                string responseString(response);
                size_t pos = responseString.find("{\"token\":\"");
                if(pos != -1) {
                    token = responseString.substr(pos + 10);
                    token = token.substr(0, token.size() - 2);
                }
                close_connection(sockfd);
        }else if(command.compare("get_books") == 0){
            
            if(token.compare("") != 0) {
                string tokenToSend;
                tokenToSend += "Authorization: Bearer ";
                tokenToSend += token;
                sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
                message = compute_get_request("34.118.48.238", "/api/v1/tema/library/books", NULL, "",tokenToSend);
            }else {
                sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
                message = compute_get_request("34.118.48.238", "/api/v1/tema/library/books", NULL, "","");
            }
                puts(message);
                send_to_server(sockfd, message);
                response = receive_from_server(sockfd);
                puts(response);
                close_connection(sockfd);

        }else if(command.compare("get_book") == 0) {
            cout << "id=";
            getline(cin,id);
            
            char url[1024];
            strcpy(url,"/api/v1/tema/library/books/");
            strcat(url,id.c_str());
            if(token.compare("") != 0) {
                string tokenToSend;
                tokenToSend += "Authorization: Bearer ";
                tokenToSend += token;
                sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
                message = compute_get_request("34.118.48.238",url, NULL, "",tokenToSend);
            }else {
                sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
                message = compute_get_request("34.118.48.238", url, NULL, "","");
            }
            puts(message);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            puts(response);
            close_connection(sockfd);
        }else if(command.compare("add_book") == 0) {
            
            cout << "title=";
            getline(cin,title);
            cout << "author=";
            getline(cin,author);
            cout << "genre=";
            getline(cin,genre);
            cout << "publisher=";
            getline(cin,publisher);
            cout << "page_count=";
            getline(cin,page_count);
            json detailsBook;
            detailsBook["title"] = title;
            detailsBook["author"] = author;
            detailsBook["genre"] = genre;
            detailsBook["publisher"] = publisher;
            detailsBook["page_count"] = page_count;

            string containsBook = detailsBook.dump();

            
            if(token.compare("") != 0) {
                string tokenToSend;
                tokenToSend += "Authorization: Bearer ";
                tokenToSend += token;
                sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
                message = compute_post_request("34.118.48.238", "/api/v1/tema/library/books", "application/json",
                                               containsBook, "",tokenToSend);

            }else {
                sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
                message = compute_post_request("34.118.48.238", "/api/v1/tema/library/books", "application/json",
                                               "", "","");

            }

            puts(message);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            puts(response);
            close_connection(sockfd);
        }else if (command.compare("delete_book") == 0) {
            
            cout << "id=";
            getline(cin,id);
            char url[1024];
            strcpy(url,"/api/v1/tema/library/books/");
            strcat(url,id.c_str());
            if(token.compare("") != 0) {
                string tokenToSend;
                tokenToSend += "Authorization: Bearer ";
                tokenToSend += token;
                sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
                message = compute_delete("34.118.48.238",url, NULL, "",tokenToSend);
            }else {
                sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
                message = compute_delete("34.118.48.238", url, NULL, "","");
            }
            puts(message);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            puts(response);
            close_connection(sockfd);
        }else if(command.compare("logout") == 0) {
            
            token = "";
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            message = compute_get_request("34.118.48.238","/api/v1/tema/auth/logout", NULL, sesionCookie,"");
            puts(message);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            puts(response);
            close_connection(sockfd);
        }else if(command.compare("exit") == 0) {
                exit(0);
        }
    }
    


    return 0;
}
