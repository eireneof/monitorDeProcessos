#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cpu()
{
	for(;;)
	{ 
	}
}

void cpu_mem()
{ 
	for(;;)
	{ 
		malloc(sizeof(int));
	}
}

int string_compare(int i, char str_1[], char str_2[])
{
	if(str_1[i] == '\0' && str_2[i] == '\0')
	{
		return 0;
	}
	else
	{
		if(str_1[i] != str_2[i])
		{
			return 1;
		}
		else
		{
			return string_compare(i + 1, str_1, str_2);
		}
	}
}

int main (int argc, char *argv[], char *envp[])
{
	int pid = fork (

	char sys[100], aux[100];

	if ( pid < 0 )
	{
		perror ("Erro: ") ;
		exit (-1) ;
	}
	else if( pid > 0 ) // I'm the father process
	{
		sprintf(aux, "%d", pid);
		if(string_compare(0, argv[1], "ucp") == 0)
		{
			printf(" PID - CPU%%\n");
			strcpy(sys, "ps -e -o pid,pcpu | grep ");
			strcat(sys, aux);
		}

		else if(string_compare(0, argv[1], "ucp_mem") == 0)
		{ 
			printf(" PID - CPU%%\n");
			strcpy(sys, "ps -e -o pid,pcpu | grep ");
			strcat(sys, aux);
			strcat(sys, ";pmap ");
			strcat(sys, aux); 
			strcat(sys, " | grep -i total");
		}
		for(int i = 0; i < 1; i++)
		{
			system(sys);
			sleep(1);
		}
		strcpy(sys, "kill ");
		strcat(sys, aux);
		system(sys);
	}
	else 
	{
		if(string_compare(0, argv[1], "ucp") == 0)
		{
            cpu();
		}
		else if(string_compare(0, argv[1], "ucp_mem") == 0)
		{
			cpu_mem();
		}
	}
	perror ("Erro: ") ; /* execve did not work */

	printf ("Tchau !\n") ;
	exit(0) ; /* Terminates the process successfully (code 0) */
}
