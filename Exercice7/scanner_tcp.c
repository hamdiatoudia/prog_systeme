#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define TARGET_IP "127.0.0.1" 
#define PORT_START 0          
#define PORT_END 3000         

int main() {
    

    printf("Scan des ports TCP ouverts sur %s entre le port  %d et le port  %d\n", TARGET_IP, PORT_START, PORT_END);
    int sock;
    struct sockaddr_in target_addr;
    target_addr.sin_family = AF_INET;
    target_addr.sin_addr.s_addr = inet_addr(TARGET_IP);
    for (int i = PORT_START; i <= PORT_END; i++) 
    {
        
        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s < 0) 
        {
            perror("Erreur lors de  création de la socket");
            exit(1);
        }
        target_addr.sin_port = htons(i);
        if (connect(s, (struct sockaddr *)&target_addr, sizeof(target_addr)) == 0) 
        {
             printf("Port ouvert : %d\n", i);
        }
        close(sock);
    }
    printf("Scan terminee !\n");
    return 0;
}
