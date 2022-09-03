#ifndef HTTPREQUEST_H_INCLUDED
#define HTTPREQUEST_H_INCLUDED


//enumerate the HTTP Methods

enum HTTPMethods{

    GET,
    POST,
    PUT,
    HEAD,
    PATCH,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE
};

//defining the HTTPRequest

struct HTTPRequest{

    int Method;
    char *URI;
    float HTTPVersion;
};


//defining the http request constructor

struct HTTPRequest http_request_constructor(char *request_string);

#endif // HTTPREQUEST_H_INCLUDED
