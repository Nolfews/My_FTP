/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** signal_handler
*/

#include "../include/server.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int sig)
{
    printf("\nReçu signal %d, arrêt du serveur...\n", sig);
    exit(0);
}

void setup_signal_handler(void)
{
    if (signal(SIGINT, handle_signal) == SIG_ERR) {
        perror("Erreur lors de la configuration du gestionnaire de signal");
        exit(84);
    }
}
