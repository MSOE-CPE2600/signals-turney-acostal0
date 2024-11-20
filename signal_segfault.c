/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * File: signal_segfault
 * Assignment: Lab 10 Section 121
 * Modified by: Lizbeth Acosta
 * 
 * Brief summary of modifications:
 * 
 * Without the signal handler, the program would simply 
 * terminate with a segmentation fault message.
 * With the handler, the program catches the SIGSEGV 
 * signal and prints the message without crashing immediately.
 * 
 * gcc -o signal_segfault signal_segfault.c
 * ./signal_segfault
 */


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


// Signal handler for SIGSEGV
void handle_segfault(int sig) {
    printf("Segmentation fault (SIGSEGV) signal caught.\n");
}

int main (int argc, char* argv[]) {
    // Register the signal handler for SIGSEGV
    signal(SIGSEGV, handle_segfault);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}