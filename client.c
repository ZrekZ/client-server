#include "server.h"
int main ()
{
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];
    int stop_signal_check;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Houston, we have a problem! The socket is resisting! ");
    }
    puts("The socket has been successfully created!");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Houston, we have a problem! Server connection lost! ");
        return 1;
    }

    puts("Server connection established! \n");

    while (1)
    {
        memset(server_reply,0,2000);
        printf("message (int) for sum > ");
        scanf("%s", message);

        if (send(sock, message, strlen(message), 0) < 0)
        {
            puts("Houston, we have a problem! Message not sent!\n");
            return 1;
        }

        if (recv(sock, server_reply, 2000, 0) < 0)
        {
            puts("Error 1234 -> recv!");
            for (int i = 0; i < 10; i++)
            break;
        }
        
        sscanf(server_reply, "%d", &stop_signal_check);
        if (stop_signal_check == 0)
        {
            puts("The session is over!");
            puts("See you soon! \n(*_*)");
            close(sock);
            return 0;
        }

        puts("The server returned the result: ");
        puts(server_reply);
        puts("\nTo exit the program, enter -> 0 \n");
    }

    close(sock);
    return 0;
}
