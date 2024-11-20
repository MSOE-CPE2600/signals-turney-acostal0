/**
 * File: signal alarm.c
 * Assignment: Lab 10 Section 121
 * Modified by: Lizbeth Acosta
 * 
 * Brief summary of program:
 * program that schedules an alarm to be sent to after 5 seconds. 
 * Prints out that the signal was received with a signal handler.
 * 
 * gcc -o signal_alarm signal_alarm.c
 * ./signal_alarm
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



void handle_alarm(int sig) {
    printf("SIGALRM signal received.\n");
    exit(1);
}

int main() {
    //register the signal handler for SIGALRM
    signal(SIGALRM, handle_alarm);

    //alarm triggers after 5 seconds
    alarm(5);

    //wait until the alarm goes off
    printf("Alarm set for 5 seconds...\n");
    while (1) {
        sleep(1);  //wait here until the alarm goes off
    }

    return 0;
}

