#include "common.h"

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int compteur = 0;

    //1. Creation du socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    //2. Initialisation 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //3. Liaison du socket avec bind
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erreur lors de la liaison");
        close(server_fd);
        exit(1);
    }

    //4. Listen sur le serveur
    if (listen(server_fd, 1) == -1) {
        perror("Erreur lors de listen");
        close(server_fd);
        exit(1);
    }

    printf("[##Serveur ##] en attente de connexion...\n");

    
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd == -1) {
        perror("Erreur lors de l'acceptation");
        close(server_fd);
        exit(1);
    }

    printf("Connexion acceptee.\n");

    while (1) {
        
        snprintf(buffer, BUFFER_SIZE, "%d",compteur);
        send(client_fd, buffer, strlen(buffer), 0);
        printf("[##Serveur ##]    : envoi compteur = %d\n",compteur);

        memset(buffer, 0, BUFFER_SIZE);
        recv(client_fd, buffer, BUFFER_SIZE, 0);
        compteur = atoi(buffer);
        printf("[##Serveur ##]    : recu compteur = %d\n", compteur);

        
        compteur++;
        sleep(1);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
