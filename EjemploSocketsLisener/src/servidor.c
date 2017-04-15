#include "servidor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int connect_server(){
	//Estructura del socket
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	direccionServidor.sin_port = htons(8080);

	//Nro de cliente
	int cliente;
	if ((cliente = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	//Valido la conexion
	if (connect(cliente, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("No se pudo conectar");
		return 1;
	}

	//Retorno nro de conexion
	return cliente;
}

void recive_data(int cliente){
	//Buffer para almacenar datos
	char *buffer = malloc(1000);
	//Recibo datos
	int bytesRecibidos = recv(cliente, buffer, 1000, 0);
	//Valido los datos
	if(bytesRecibidos <= 0){
		perror("Desconectado");
		//Falta esperar a la nueva conexion si se desconecta del servidor
	}
	//Agrego el fin de linea
	buffer[bytesRecibidos] = '\0';
	//Muestro los datos
	printf("Received: %s\n", buffer);
	//Libero la memoria del buffer
	free(buffer);
}
