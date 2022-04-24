#include "server.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/socket.h>


void *socket_thread(void *arg) {
char buf[2000];
int bytes_read;
thread_data_t *data = (thread_data_t*)arg;
if (data->socket < 0) {
perror("There is a contact !");
exit(3);
}

void* create_shared_memory(size_t size)
{
    int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANONYMOUS;
  return mmap( NULL, size, protection, visibility, -1, 0 );
}
int main()
{
    while (1) {
thread_data_t *data = malloc(sizeof(thread_data_t));
data->socket = accept(listener, 0, 0);
data->resources = &resources;
pthread_t thread;
if(pthread_create(&thread, NULL, &socket_thread, data)) {
exit(-1);
}
}
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    char client_message[2000];
    int sum = 0;
    void* shmem = create_shared_memory(128);
    pid_t childpid;
    

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1)
    {
        printf("Houston, we have a problem! The socket is resisting! ");
    }
puts("The socket has been successfully created!");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
       printf("Houston, we have a problem! The Bind is resisting! ");
        return 1;
    }

    puts("Bind has been done");
    listen(socket_desc, 3);
    puts("I'm waiting for a miracle ... (incoming connections...)");
    c = sizeof(struct sockaddr_in);

    while (1)
    {

        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);

        if (client_sock < 0)
        {
            perror("Houston, we have a problem! we lost the socket!");
            return 1;
        }

        char char_sock[2000];
        sprintf(char_sock, "%d", client_sock);
        puts("Connection is ready.\nClient socket:");
        puts(char_sock);

        if ((childpid = fork()) == 0)
        {
            close(socket_desc);

            while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
            {
                puts(" >>");
                int client_number = -1000000;
                sscanf(client_message, "%d", &client_number);
                if(client_number == -1000000)
                {
                    puts("Client socket:");
                    puts(char_sock);
                    puts("Client > ");
                    puts(client_message);
                    puts("Server > ");
                    puts("Well ... what are you entering ?!");
                    puts(" >>");
                    write(client_sock, "Re-enter ... ",  12);
                    memset(client_message,0,2000);
                }
                else if (client_number == 0)
                {
                    memset(client_message,0,2000);
                    puts("Time to say good-bye (Session off)" );
                    puts("See you soon! \n(*_*)");
                    puts(char_sock);
                    puts(" >>");
                    write(client_sock, stop_signal,  1);
                    close(client_sock);
                    close(socket_desc);
                    pause();
                    return 0;
                }
                else
                {
                    sscanf(shmem, "%d", &sum);
                    memset(shmem,0,128);
                    sum = sum + client_number;
                    char result[200];
                    char client_number_char[200];
                    sprintf(client_number_char, "%d", client_number);
                    sprintf(result, "%d", sum);
                    memcpy(shmem, result, strlen(result));
                    puts("Client socket:");
                    puts(char_sock);
                     puts("Client > ");
                    puts(client_number_char);
                    puts("Server > ");
                    puts(shmem);
                    puts(" ");
                    write(client_sock, result,  strlen (result));
                    memset(client_message,0,2000);
                }
                
            }
            
            if (read_size == 0)
            {
                puts("The client has left us!");
                fflush(stdout);
                puts(" >>");
            }
            else if (read_size == -1)
            {
               perror("Error 1234 -> recv!");
            }
        }
    }
    close(client_sock);
    exit(0);
}