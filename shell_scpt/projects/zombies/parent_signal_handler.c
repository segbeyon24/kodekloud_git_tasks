// Implementing a dedicated signal handler in the parent
// to properly process child termination signals across 
// the parent's lifetime.
//
// This code reaps all zombie processes upon receiving
// the SIGCHILD signal.
//
// Date: Friday, 06-12-2024
// source_url: https://www.site24x7.com/learn/linux/how-to-kill-zombie-process-in-linux.html
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <signal.h>
# include <sys/wait.h>


//Signal handler function to reap zombie processes
void sigchld_handler(int signum) {
	pid_t pid;
	int status;

	// Reap all zombie processes
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
		PRINTF("Parent process reaped child process with 
				PID %d.\n", pid);
	} 
}


int main() {
pid_t child_pid;
struct sigaction sa;

// Register the signal handler for SIGCHLD
sa.sa_handler = sigchld_handler;
sigemptyset(&sa.sa_mask);
sa.sa_flags = SA_RESTART;

if (sigaction(SIGCHLD, &sa, NULL) == -1) {
	perror("sigaction");
	exit(EXIT_FAILURE);
}


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
	printf("Parent process is running and will continue to run.\n");
	// Parent proccess continues running and will periodically rea
	// zombie processes
	
	while (1) {
		sleep(5); // Sleep for a while to allow child processes
		// to terminate
		printf("Parent process is still running.\n")
	}
}

return 0;
}

// compile with gcc [filename] temp
// run with ./[filename]
// expected output: the parent is able to reap the child process
// without terminating or encountering any issues.
