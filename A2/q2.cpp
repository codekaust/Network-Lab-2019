#include <stdio.h> 
#include <sys/wait.h>
#include <bits/stdc++.h>
#include <unistd.h> 

using namespace std;

int main() {

	cout << "Parent's process id: " << getpid() << endl << endl;

	pid_t child_pid = fork(); 

    if (child_pid > 0) {
    	cout << "Parent active..." << endl;
    	sleep(4);
    	cout << "Parent terminated" << endl;
    }
    else if (child_pid == 0) {        
    	cout << "Child created with pid "<< getpid() << " from parent pid " << getppid() << endl;   	
    	child_pid = fork();
    	if(child_pid > 0) {
    		sleep(1);
    		cout << "Child sleeping..." << endl;
    		sleep(2);
    		cout << "Child awake again and active!" << endl;
    		sleep(2);
      		cout << "Child is now orphan!" << endl << endl;
    	}
    	else if(child_pid == 0) {
    		cout << "Grandchild created with pid "<< getpid() << " from parent pid " << getppid() << endl << endl;
    		sleep(1);
    		cout << "Terminating grandchild" << endl;
    		cout << "Grandchild is now zombie" << endl << endl;
    	}
    }
  
    return 0;
}
