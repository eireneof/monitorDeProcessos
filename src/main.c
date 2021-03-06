#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500
#define CHILD_ID 0
#define PARENT_ID 1
#define ERROR -1
#define DEBUG(x) if(x)

void cpu() // Tests CPU;
{
	for(;;)
	{}
}

void cpu_mem() // Tests CPU and memory;
{ 
	for(;;)
	{ 
		malloc(sizeof(int));
	}
}

int string_compare(int i, char str_1[], char str_2[]) // Compares two strings
{
	if(str_1[i] == '\0' && str_2[i] == '\0') return 0; // If it reaches the end, the function returns 0;

	else
	{
		if(str_1[i] != str_2[i]) // If it find two different letters;
		{
			return 1;
		}
		else // Else, it will look for the next letters
		{
			return string_compare(i + 1, str_1, str_2);
		}
	}
}

int main (int argc, char *argv[], char *envp[])
{
	int pid = fork(); // Creates a new process;
	char cmd[MAX], id[MAX]; // "cmd" stores the bash command and "id", the process ID;

	if (pid <= ERROR) // if creating a child process didn't work
	{
		perror ("Error: ");
		exit (ERROR);
	}
	else if(pid >= PARENT_ID) // If I'm the parent process
	{
		sprintf(id, "%d", pid); //Converts the PID (int) into a string
		if(string_compare(0, argv[1], "ucp") == 0) // If argv[1] == "ucp"
		{
            printf("==== CPU TEST ====\n"); // Print a header
			printf(" PID - %%CPU\n"); // Print another header
			strcpy(cmd, "ps -e -o pid,pcpu | grep "); // Saves the command in the string "cmd", using "grep" as a filter
			strcat(cmd, id); // Concatenates the process ID
		}
		else if(string_compare(0, argv[1], "ucp_mem") == 0) // If argv[1] == "ucp_mem"
		{ 
            printf("==== CPU & MEMORY TEST ====\n"); // Print a header
			printf(" PID - %%CPU\n");// Print another header
			strcpy(cmd, "ps -e -o pid,pcpu | grep "); // Saves the command in the string "cmd", using "grep" as a filter
			strcat(cmd, id); // Concatenates the process ID
			strcat(cmd, ";pmap "); // Concatenates "pmap", wich is used for show the memory usage
			strcat(cmd, id); // Concatenates the process ID
			strcat(cmd, " | grep -i Total");
		}

		for(int i = 0; i < 1; i++) // Executes the command during 10 seconds
		{
			system(cmd); // Executes the command
			sleep(1); // Wait one second;
		}

		strcpy(cmd, "kill "); // "kill" is used for kill the child process
		strcat(cmd, id);
		system(cmd); // Kill the child process
	}
	else // If I'm the child (pid == CHILD_ID)
	{
		if(string_compare(0, argv[1], "ucp") == 0) // If argv[1] == "ucp"
		{
            cpu();
		}
		else if(string_compare(0, argv[1], "ucp_mem") == 0) // If argv[1] == "ucp_mem"
		{
			cpu_mem();
		}
	}
	perror ("Error: "); /* execve did not work */
	printf ("Tchau !\n");
	exit(0); /* Terminates the process successfully (code 0) */
}