/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/*********************************************
 * Filename: signal_handler.c
 * Assignment: Lab 10 Section 121
 * Modified by: Lizbeth Acosta
 * 
 * Brief summary of modifications:
 * Sent SIGINT to the process by CTRL+c or by the kill
 * command. The behavior when the SIGINT signal is received 
 * it will invoke the handel_signal function and print the message
 * and end the program with exit(1).
 * 
 * After modifying:
 * No longer exits inside the signal handler. CTRL+c 
 * or kill -SIGINT <PID> no longer makes the program terminate. 
 * The message will still print when SIGINT is 
 * received but won't terminate. This means that 
 * the bahvior is still the same except it won't exit anymore
 * unless it is SIGKILL.
 * The only way to end the program is to go into the
 * terminal and enter "kill -SIGKILL <PID>" to kill the 
 * program. 
 * 
 * gcc -o signal_handler signal_handler.c
 * ./signal_handler
 * 
 * kill -SIGKILL <PID> - in another terminal
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message 
 */
void handle_signal() {
    printf("\nReceived a signal.\n");
    //exit(1);
}

int main() {
    pid_t pid = getpid();
    printf("PID: %d\n", pid);

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}