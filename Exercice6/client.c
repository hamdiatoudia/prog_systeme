#include "common.h"

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int compteur;

    // Création du socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Erreur lors de la création du socket");
        exit(1);
    }

    // Initialisation du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connexion au serveur
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erreur lors de la connexion");
        close(client_fd);
        exit(1);
    }

    printf("Connecté au serveur.\n");

    while (1) {
        
        memset(buffer, 0, BUFFER_SIZE);
        recv(client_fd, buffer, BUFFER_SIZE, 0);
        compteur = atoi(buffer);
        printf("[##Client##]   : recu compteur = %d\n", compteur);
        compteur++;
        sleep(1);
        snprintf(buffer, BUFFER_SIZE, "%d", compteur);
        send(client_fd, buffer, strlen(buffer), 0);
        printf("[##Client ##]  : envoi compteur = %d\n", compteur);
    }
     close(client_fd);
    return 0;
}
