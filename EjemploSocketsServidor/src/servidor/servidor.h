#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DatosRecibidosType{
	char *datos;
	int bytesRecibidos;
}DatosRecibidos;

int connect_server(char* IP , int Port);
int build_server(int Port);
void set_listen(int servidor, int sizeConexiones);
int accept_conexion(int servidor, fd_set *master, int fdmax);
void massive_send(int fdmax, fd_set *master, DatosRecibidos * buffer, int i, int servidor);
DatosRecibidos * recive_data(int cliente);

DatosRecibidos * DatosRecibidos_new(char *datos,int bytesRecibidos);
void DatosRecibidos_free(DatosRecibidos *this);

#endif
