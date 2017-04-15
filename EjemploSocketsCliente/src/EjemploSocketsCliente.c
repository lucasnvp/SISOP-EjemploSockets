/*
 ============================================================================
 Name        : EjemploSocketsCliente.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "servidor.h"

int main(void) {
	//Me conecto al servidor
	int servidor = connect_server();

	//Si conecto, informo
	if(servidor > 0){
		printf("Ready to send \n");
	}

	//Bucle para el ingreso de datos
	while (1) {
		//Mensaje
		char* mensaje = malloc(1000);
		scanf("%s", mensaje);
		//Envio el mensaje
		send(servidor, mensaje, strlen(mensaje), 0);
		free(mensaje);
	}

	return 0;
}
