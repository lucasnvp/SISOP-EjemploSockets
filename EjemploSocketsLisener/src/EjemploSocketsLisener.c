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
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	direccionServidor.sin_port = htons(PORT);

	int cliente = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(cliente, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("No se pudo conectar");
		return 1;
	}

	printf("Estoy escuchando\n");
	listen(cliente, CANTCONECIONES);

	//Recibiendo datos
	char* buffer = malloc(1000);

	while(1){
		int bytesRecibidos = recv(cliente, buffer, 1000, 0);
		if(bytesRecibidos <= 0){
			perror("Desconectado");
			return 1;
		}

		buffer[bytesRecibidos] = '\0';
		printf("Received: %s\n", buffer);
	}


	free(buffer);

	return 0;

}
