/*********************************************
 * Filename: receiving.c
 * Assignment: Lab 10
 * Description: 
 * 1. Installs a signal handler for the ‘ball’ signal, the signal handler should 
 * determine the process that sent the signal (the other player)
 * 2. Waits for a random amount of time between 1 and 2 seconds
 * 3. Sends the signal (the ball) back to the sender
 * 4. For each step (receiving signal, sending signal), the program should print out 
 * a status message to indicate what it is doing. Also play the system bell (‘’ or 
 * ‘\007’) to simulate a ball being hit.

 * Author: Lizbeth Acosta
 * Date: 11/19/24
 * Note: 
 * $ gcc -o receiving receiving.c
 * $ ./receiving 
 *********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int count = 0;
pid_t server_pid;

void handle_signal(int sig, siginfo_t *info, void *context) {
    if (sig == SIGUSR1) {
        //ball received
        printf("PLayer 2 hits to player 1\n");

        //hitting the ball back
        sleep(rand() % 2 + 1);
        printf("Player 1's turn\n");
        
        //sends the ball back
        if (count < 10) {
            union sigval value;
            value.sival_int = count; //set the count to pass with the signal
            sigqueue(info->si_pid, SIGUSR1, value); //send the signal back with updated count
            count++; //add 1 to the count after sending
        } else {
            printf("Game over! winner: Player %d, %d volleys\n", info->si_pid, count);
            exit(0);
        }
    }
}

int main() {
    srand(time(NULL));

    //print PID
    printf("Receiver waiting. PID: %d\n", getpid());

    //signal handler, register SIGUSR1 with the custom handler
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL); //&sa contains new handler info

    printf("Waiting for the ball.\n");

    //wait
    while (1) {
        pause();
    }

    return 0;
}
