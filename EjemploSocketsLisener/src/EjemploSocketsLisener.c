/*
 ============================================================================
 Name        : EjemploSocketsLisener.c
 Author      : Lucas Visser
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080	// puerto en el que escuchamos
#define CANTCONECIONES 10 	// Si quiero el maximo de conexiones posibles en el sockect reemplazar por 'SOMAXCONN'

int main(void) {
	//Conexion al servidor
	int cliente = connect_server();

	//Si conecto, informo
	if(cliente > 0){
		printf("Estoy escuchando\n");
	}

	while(1){
		//Recibo los datos
		recive_data(cliente);
	}

	return 0;

}
