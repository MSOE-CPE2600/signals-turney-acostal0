/*********************************************************************************
 * Filename: server.c
 * Assignment: Lab 10
 * Description: 
 * 1. Installs a signal handler for the ‘ball’ signal, the signal handler should 
 * determine the process that sent the signal (the other player)
 * 2. Waits for a random amount of time between 1 and 2 seconds
 * 3. Sends the signal (the ball) back to the sender
 * 4. For each step, the program should print out a status message to indicate 
 * what it is doing and play the system bell when sending the signal (hitting the 
 * ball)
 * 5. After the server sets up the signal handler, it should serve the ball (send the 
 * signal) to the other player
 * Author: Lizbeth Acosta
 * Date: 11/19/24
 * Note: 
 * $ gcc -o serving serving.c
 * $ ./serving <PID from receiving>
 *************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int count = 0;


void handle_signal(int sig, siginfo_t *info, void *context) {
    if (sig == SIGUSR1) {
        printf("Player 1 hits to player 2\n");

        // this simulates hitting the ball back with a random delay
        sleep(rand() % 2 + 1);  //sleep random
        printf("Player 2's turn\n");

        //this sends the ball back with the number of volleys
        if (count < 10) {
            union sigval value;
            value.sival_int = count; //set the count to pass with the signal
            sigqueue(info->si_pid, SIGUSR1, value); //send the signal back with updated count
            count++; //add 1 to the count after sending
        } else {
            printf("Game over! Winner: Player %d wins, %d volleys\n", info->si_pid, count);
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    pid_t pid;
    srand(time(NULL));

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
        exit(1);
    }
    pid = atoi(argv[1]);

    //register SIGUSR1 with the custom handler
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    //send ball
    printf("Server ready. Serving the first ball...\n");
    union sigval value;
    value.sival_int = count; //set the count to pass with the signal
    sigqueue(pid, SIGUSR1, value); //send the signal back with updated count

    //wait for signal
    while (1) {
        pause();
    }

    return 0;
}
