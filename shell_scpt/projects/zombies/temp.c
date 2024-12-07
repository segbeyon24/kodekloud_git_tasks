#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
pid_t child_pid;

// Create a child process
child_pid = fork();

if (child_pid < 0) {

	// Fork failed
	perror("fork");
	exit(EXIT_FAILURE);

} else if (child_pid == 0) {
	// Child process
	printf("Child process is running.\n");
	// Child process exits immediately
	
} else {
	// Parent process
	printf("Parent process is running.\n");
	// Parent proccess sleeps for a while. During this time
	// the child could become a zombie
	sleep(30);
}
return 0;
}
