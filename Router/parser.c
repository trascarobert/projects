#include "parser.h"

int read_rtable(char *filename,struct route_table_entry **routeTableEntry) {
    int routeTableSize = 0;
    FILE* input = fopen(filename,"r");
    char *buffer = (char *)malloc(100 * sizeof(char));
    struct in_addr inAddr;
    while(fgets(buffer,100,input)) {
        char *save;
        char *token = strtok_r(buffer," ",&save);
        inet_aton(token,&inAddr);
        (*routeTableEntry)[routeTableSize].prefix = ntohl(inAddr.s_addr);
        char *save1;
        token = strtok_r(save, " ",&save1);
        inet_aton(token,&inAddr);
        (*routeTableEntry)[routeTableSize].next_hop = ntohl(inAddr.s_addr);
        char *save2;
        token = strtok_r(save1, " ",&save2);
        inet_aton(token,&inAddr);
        (*routeTableEntry)[routeTableSize].mask = ntohl(inAddr.s_addr);
        char *save3;
        token = strtok_r(save2, " \n",&save3);
        (*routeTableEntry)[routeTableSize].interface = atoi(token);
        routeTableSize++;
        *routeTableEntry = realloc(*routeTableEntry,(routeTableSize + 1)*sizeof(struct route_table_entry));
    }
    return routeTableSize;
}

