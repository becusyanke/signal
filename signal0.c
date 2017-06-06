#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void manejador( int sig );

int main() {

	if( signal(SIGINT, manejador) == SIG_ERR ) {
		perror("Error en la senal \n");
		exit(EXIT_FAILURE);
	}

	while(1)
		pause();

	return 0;
}


void manejador( int sig )
{

	if(sig == SIGINT)
		printf("No voy a terminar, jejeje... \n");
	else if (sig == SIGTERM)
		printf("Que no\n");
/*	if( signal(SIGINT,manejador ) == SIG_ERR )
	{
		perror("Error en la senal \n");
		exit(EXIT_FAILURE);
	}
*/
}
