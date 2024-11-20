/**
 * File: signal_sigaction.c
 * Assignment: Lab 10 Section 121
 * Modified by: Lizbeth Acosta
 * 
 * Brief summary of program:
 * registers a handler for SIGUSR1 that prints the sender's process ID (PID) 
 * with the siginfo_t structure, enabled by the SA_SIGINFO flag. After registration, 
 * the program enters an infinite loop, waiting for signals. Can send SIGUSR1 with 
 * kill -SIGUSR1 <PID> to the process, and the program prints the sender's PID upon 
 * receiving the signal without terminating.
 * 
 * gcc -o signal_sigaction signal_sigaction.c
 * ./signal_sigaction
 * 
 * kill -SIGUSR1 <PID> - to send signal
 */


#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigusr1(int sig, siginfo_t *info, void *context) {
    printf("Received SIGUSR1 from process with PID: %d\n", info->si_pid);
}

int main() {
    //define the sigaction structure
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;  //enable extended signal information
    sa.sa_sigaction = handle_sigusr1;

    //register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    //PID
    printf("PID: %d\n", getpid());

    while (1) {
        pause();  //wait for a signal
    }

    return 0;
}
