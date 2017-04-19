/*
 ============================================================================
 Name        : EjemploSockets.c
 Author      : Lucas Visser
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Sockets - Crear un servidor
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "servidor/servidor.h"

#define PORT 8080   		// puerto en el que escuchamos
#define CANTCONECIONES 10 	// Si quiero el maximo de conexiones posibles en el sockect reemplazar por 'SOMAXCONN'

int main(void)
{
    fd_set master;   // conjunto maestro de descriptores de fichero
    fd_set read_fds; // conjunto temporal de descriptores de fichero para select()
    int fdmax;        // número máximo de descriptores de fichero
    int i;
    FD_ZERO(&master);    // borra los conjuntos maestro y temporal
    FD_ZERO(&read_fds);

    //Creacion del servidor
	int servidor = build_server(PORT);

    //El socket esta listo para escuchar
	if(servidor > 0){
		printf("Servidor escuchando\n");
	}

    // Seteo la cantidad de conexiones
	set_listen(servidor, CANTCONECIONES);

    // añadir listener al conjunto maestro
    FD_SET(servidor, &master);

    // seguir la pista del descriptor de fichero mayor
    fdmax = servidor; // por ahora es éste

    // bucle principal
    for(;;) {
        read_fds = master; // cópialo
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }
        // explorar conexiones existentes en busca de datos que leer
        for(i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // ¡¡tenemos datos!!
                if (i == servidor) {
                	// acepto una nueva conexion
                	fdmax = accept_conexion(servidor, &master, fdmax);
                } else {
                	DatosRecibidos * buffer = recive_data(i);
                    // gestionar datos de un cliente
                	if(buffer <= 0){
                		FD_CLR(i, &master); // eliminar del conjunto maestro
                	}else {
                		//Manda la info a todos
                		massive_send(fdmax, &master, buffer, i, servidor);
                    }
                }
            }
        }
    }

    return 0;
}
