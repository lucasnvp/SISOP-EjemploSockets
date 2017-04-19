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

#include "servidor/servidor.h"

int main(void) {
	//Conexion al servidor
	int cliente = connect_server("127.0.0.1",8080);

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
