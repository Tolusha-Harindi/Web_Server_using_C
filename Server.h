#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED


#include <sys/socket.h>
#include <netinet/in.h>

//defining the Server

struct Server{

    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct Server *server);

};

//defining the Sever Constructor function

struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*launch)(struct Server * server));

#endif // SERVER_H_INCLUDED
