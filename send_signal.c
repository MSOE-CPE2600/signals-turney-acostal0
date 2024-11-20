/**
 * File: send_signal.c
 * Assignment: Lab 10 Section 121
 * Modified by: Lizbeth Acosta
 * 
 * Brief summary of program:
 * Uses sigqueue to send SIGUSR1 to the receiving program, 
 * along with a random integer generated using rand() seeded with srand(time(NULL)).
 * Prints the random integer before sending the signal.
 * 
 * gcc -o send_signal send_signal.c
 * gcc -o recv_signal recv_signal.c
 * 
 * ./recv_signal - in one terminal
 * ./send_signal <PID> - in another terminal
 * 
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid = atoi(argv[1]);

    srand(time(NULL));
    int random_value = rand() % 100; //generates random number

    union sigval value;
    value.sival_int = random_value;

    //prints the random number being sent
    printf("Sending value: %d to PID: %d\n", random_value, pid);

    //send signal
    if (sigqueue(pid, SIGUSR1, value) == -1) {
        perror("sigqueue");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


