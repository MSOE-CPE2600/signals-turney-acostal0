/**
 * File: recv_signal.c
 * Assignment: Lab 10 Section 121
 * Modified by: Lizbeth Acosta
 * 
 * Brief summary of program:
 * registers a signal handler for SIGUSR1 using sigaction.
 * The signal handler extracts the sival_int field (an integer value sent 
 * along with the signal) from the siginfo_t structure and prints it.
 * The program waits in an infinite loop after setting up the handler.
 * 
 * gcc -o send_signal send_signal.c
 * gcc -o recv_signal recv_signal.c
 * 
 * ./recv_signal - in one terminal
 * ./send_signal <PID> - in another terminal
 * 
 * 
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_signal(int sig, siginfo_t *info, void *context) {
    printf("Received value: %d\n", info->si_value.sival_int); //gets the int value sent with the signal
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO; //enable detailed signal information
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);

    //register SIGUSR1 with the custom handler
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for signals. PID: %d\n", getpid());

    while (1) {
        pause(); //wait for a signal
    }

    return 0;
}

