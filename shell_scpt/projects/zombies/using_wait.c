/*
 * Best practice is to make add wait() to avoid 
 * zombies altogether
 *
 * Date: Friday, 06/12/2024
 * */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
pid_t child_pid, wait_pid;
int status;

// Create a child process
child_pid = fork();

if (child_pid < 0) {

	// Fork failed
	perror("fork");
	exit(EXIT_FAILURE);

} else if (child_pid == 0) {
	// Child process
	printf("Child process is running.\n");
	sleep(2); // Simulate some work
	exit(EXIT_SUCCESS); // Exit the child process
	
} else {
	// Parent process
	printf("Parent process is running.\n");

	// Wait for the child process to terminate
	wait_pid = wait(&status);

	if (wait_pid == -1) {
		perror("wait");
		exit(EXIT_FAILURE);
	}

	printf("Child process with PID %d has terminated.", wait_pid);
}
return 0;
}
