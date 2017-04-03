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
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void) {
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = INADDR_ANY;
	direccionServidor.sin_port = htons(8080);

	int servidor = socket(AF_INET, SOCK_STREAM, 0);

	//Flag para que se pueda volver a utilizar el puerto si se cierra con 'ctrl + c'
	int activado = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

	//Validacion por si es puerto esta en uso.
	if(bind(servidor,(void*) &direccionServidor, sizeof(direccionServidor)) != 0){
		perror("Fallo el bind");
		return 1;
	}

	printf("Estoy escuchando\n");
	//100 a modo de ejemplo
	//Si quiero el maximo posible reemplazar por 'SOMAXCONN'
	listen(servidor, 100);

	//Para recibir conexiones.
	struct sockaddr_in direccionCliente;
	unsigned int tamanoDireccion = sizeof(struct sockaddr_in);
	int cliente = accept(servidor, (void*) &direccionCliente, &tamanoDireccion);

	printf("Recibí una conexión en %d!!\n", cliente);
	send(cliente, "Hola NetCat!", 13, 0);

	//Recibiendo datos
	char* buffer = malloc(1000);

	while(1){
		int bytesRecibidos = recv(cliente, buffer, 1000, 0);
		if(bytesRecibidos <= 0){
			perror("Desconectado");
			return 1;
		}

		buffer[bytesRecibidos] = '\0';
		printf("Me llegaron %d bytes con %s\n", bytesRecibidos, buffer);
	}


	free(buffer);

	return 0;

}
