#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <stdbool.h>
#include <string.h>

int connect_server(char* IP , int Port);
void recive_data(int cliente);

#endif
