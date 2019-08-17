#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cpu()
{ // Function that tests the processor
	for(;;)
	{ // Infinite loop for the test of processor
	}
}

void cpu_mem()
{ // Function that tests the memory and processor
	for(;;)
	{ // Infinite loop for the test of processor
		malloc(sizeof(int)); // Allocates an integer to each loop for the memory test
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
	int pid = fork () ; // Process identifier

	char sys[100], aux[100];

	if ( pid < 0 ) /* If the fork did not work */
	{
		perror ("Erro: ") ;
		exit (-1) ; /* Closes the process with error code -1 */
	}
	else if( pid > 0 ) // If I'm the father
	{
		sprintf(aux, "%d", pid); // Converts the child pid to string and passes this value to aux variable

		if(string_compare(0, argv[1], "ucp") == 0)
		{ // If it's just the processor test
			printf(" PID - CPU%%\n"); // Prints on the screen a header for better visual identification of the values
			strcpy(sys, "ps -e -o pid,pcpu | grep "); // Saves in the variable 'sys' the command that brings to the screen the values ​​of the pid and the percentage of cpu used by a process with 'grep' to filter from the pid
			strcat(sys, aux); // Concatenates the sys string and the pid value to be parsed
		}

		else if(string_compare(0, argv[1], "ucp_mem") == 0)
		{ // If the test is processor and memory
			printf(" PID - CPU%%\n"); // Prints on the screen a header for better visual identification of values
			strcpy(sys, "ps -e -o pid,pcpu | grep ");// Saves in the variable 'sys' the command that brings to the screen the values ​​of the pid and the percentage of cpu used by a process with 'grep' to filter from the pid
			strcat(sys, aux);// Concatenates the sys string and the pid value to parse
			strcat(sys, ";pmap ");// Concatenates to her also a ';' to indicate command end and 'pmap' to identify how many Kb of memory are being used by the process
			strcat(sys, aux); // With the process pid the program filters which process must have the monitored memory
			strcat(sys, " | grep -i total"); // With the use of grep here, shows only the total memory used
		}
		for(int i = 0; i < 1; i++)
		{// While 10 seconds pass, do
			system(sys); // Calls the system and executes the command determined by the if-else-if above and executes it
			sleep(1); // Wait a second
		}
		strcpy(sys, "kill ");// Sends to sys a new value for the command 'kill'
		strcat(sys, aux); // With the child process pid saved in 'aux'
		system(sys); // Executes the command 'kill * pid *' killing the child process after 10 seconds of execution
	}
	else // If i'm the son process
	{
		if(string_compare(0, argv[1], "ucp") == 0)
		{ // If the argv parameter [1] indicates that the program should test only the cpu enters this if
			cpu(); // Calls the cpu () function that has an infinite loop to force the processor
		}
		else if(string_compare(0, argv[1], "ucp_mem") == 0)
		{ // Otherwise, if the parameter indicates that the program should test the cpu and the memory enters here
			cpu_mem(); // Calls the cpu_mem function that has an infinite loop to force the processor and in each loop a call to the malloc function allocating the number of bytes of an integer to force the memory
		}
	}
	perror ("Erro: ") ; /* execve did not work */

	printf ("Tchau !\n") ;
	exit(0) ; /* Terminates the process successfully (code 0) */
}
