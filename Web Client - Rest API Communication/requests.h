#ifndef _REQUESTS_
#define _REQUESTS_

#include <string>
using namespace std;

// computes and returns a GET request string (query_params
// and cookies can be set to NULL if not needed)
char *compute_get_request(char *host, char *url, char *query_params,
                           string cookies,string token);

// computes and returns a POST request string (cookies can be NULL if not needed)
char *compute_post_request(char *host, char *url, char* content_type, string body_data,
                           string cookies,string token);

char *compute_delete(char *host, char *url, char *query_params,
                     string cookies,string token);

#endif
