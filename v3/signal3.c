#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_PROC 4

void proceso_hijo( int np );
void proceso_padre();
void manejador( int sig );
void manejadorTemp( int sig );

pid_t pid[NUM_PROC];
int bandera = 1;

int main() {
	register int np;

	if( signal(SIGALRM, manejadorTemp) == SIG_ERR )
	{
		perror("Error en la senal\n");
		exit(EXIT_FAILURE);
	}

	if( signal(SIGUSR1, manejador) == SIG_ERR )
	{
		perror("Error en la senal\n");
		exit(EXIT_FAILURE);
	}

	for (np = 0; np < NUM_PROC; np++) {
		pid[np] = fork();

		if ( pid[np] == -1) {
			perror("Error al generar el proceso");
			exit (EXIT_FAILURE);
		} else if ( !pid[np] ) {
			proceso_hijo( np );
		}
	}

	proceso_padre();

	return 0;
}

void proceso_hijo( int np ) {

	printf("Proceso %d con pid %d ejecutado\n", np, getpid() );

	while (bandera);

	printf("Senal recibida en el proceso hijo\n");

	exit( np );
}

void proceso_padre() {
	register int i;
	int np;
	pid_t pidr;

	alarm(5);

	for ( i = 0; i < NUM_PROC; i++ ) {
		pidr = wait( &np );
		np = np >> 8;
		printf("Proceso %d con pid %d terminado \n", np, pidr);
	}
}

void manejador( int sig ) {
	printf("Recibiendo senal en el manejador...\n");
	bandera = 0;
}

void manejadorTemp( int sig ) {
	static int i = 0;
	alarm(5);

	if ( i < NUM_PROC ) {
		kill(pid[i++], SIGUSR1);
	}

}
