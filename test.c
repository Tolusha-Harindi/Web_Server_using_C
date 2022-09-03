#include "Server.h"
#include "HTTPRequest.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>

//server launch function

void launch(struct Server *server){


    struct HTTPRequest request;
    char buffer[30000]; //to get the HTTP request
    int fdimg;

    while(1){

    printf(" ===== WAITING FOR A CONNECTION ======\n ");

    int address_length = sizeof(server->address);
    int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
    read(new_socket, buffer, 30000);
    printf("%s\n", buffer);

    struct HTTPRequest request = http_request_constructor(&buffer);

    printf("%s\n", request.URI);

    //loading the pages and other file types based on the URI

    if(strcmp(request.URI, "/") == 0){

        FILE *html_data;
        html_data = fopen("/home/thavindu/Git/web_server/index.html", "r");

        char response_data[1024];
        fgets(response_data, 1024, html_data);

        char http_header[3000] = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win 32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Type:text/html\nConnection: Closed\n\n";
        strcat(http_header, response_data);

        write(new_socket, http_header, strlen(http_header));
        fclose(html_data);
        close(new_socket);

    }else if(strcmp(request.URI, "/favicon.ico") == 0){

            fdimg = open("favicon.ico", O_RDONLY);
            sendfile(new_socket, fdimg, NULL, 16000);
            close(fdimg);
            close(new_socket);
    }
    else if(strcmp(request.URI, "/cat.jpeg") == 0){

            fdimg = open("cat.jpeg", O_RDONLY);
            sendfile(new_socket, fdimg, NULL, 45000);
            close(fdimg);
            close(new_socket);
    }
    else if(strcmp(request.URI, "/about") == 0){

        FILE *html_data;
        html_data = fopen("/home/thavindu/Git/web_server/about.html", "r");

        char response_data[1024];
        fgets(response_data, 1024, html_data);

        char http_header[3000] = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win 32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Type:text/html\nConnection: Closed\n\n";
        strcat(http_header, response_data);

        write(new_socket, http_header, strlen(http_header));
        fclose(html_data);
        close(new_socket);

    }else if(strcmp(request.URI, "/profile") == 0){


        FILE *html_data;
        html_data = fopen("/home/thavindu/Git/web_server/profile.html", "r");

        char response_data[1024];
        fgets(response_data, 1024, html_data);

        char http_header[3000] = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win 32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Type:text/html\nConnection: Closed\n\n";
        strcat(http_header, response_data);

        write(new_socket, http_header, strlen(http_header));
        fclose(html_data);
        close(new_socket);

    }
    else{ //Error page for the sever if page can't be found.

        FILE *html_data;
        html_data = fopen("/home/thavindu/Git/web_server/error.html", "r");

        char response_data[1024];
        fgets(response_data, 1024, html_data);

        char http_header[3000] = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win 32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Type:text/html\nConnection: Closed\n\n";
        strcat(http_header, response_data);

        write(new_socket, http_header, strlen(http_header));
        fclose(html_data);
        close(new_socket);

    }

  }

}

int main(){

    //constructing the server by passing arguments

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0 , INADDR_ANY, 5000, 10, launch);
    server.launch(&server); //launching the sever

}
