#include <unistd.h> 
#include <stdio.h> 
#include <sys/wait.h>
#include <stdlib.h>

int main(){

	printf("The process id for Parent: %d\n",getpid());

	for(int i = 0; i < 2; i++){
		if(fork() == 0){
			printf("Child: %d, has pid: %d, parent pid: %d\n",(i+1),getpid(),getppid());

			for(int j = 0; j < 2; j++){
				if(fork() == 0){
					printf("Grandchild: %d, has pid: %d and parent pid: %d\n",(i*2 + 1 + j),getpid(),getppid());
					exit(0);	// grandchild process terminates execution
				}
				wait(NULL);		// child process waits for grandchild process to complete  execution
			}
			
			exit(0);		// child process terminates execution
		}
		wait(NULL);			// parent process waits for child process to terminate execution
	}
	
	exit(0);
}