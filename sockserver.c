#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

int srv_sock_fd;
int server_fd = -300;

/**
 * [start_server description]
 * @param arg [description]
 */
void* start_server(void* arg){  
  printf("starting server\n");

  srv_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(srv_sock_fd < 0)
  {
    printf("server socket() error\n");
    return NULL;
  }

  struct sockaddr_in sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(29493);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((bind(srv_sock_fd, (struct sockaddr *)&sa, sizeof(sa))) < 0) {
     printf("server bind() error\n");
     return NULL;
  }

  int wait_size = 1;  // maximum number of waiting clients
  if (listen(srv_sock_fd, wait_size) < 0) {
     printf("server listen() error\n");
     return NULL;
  } else {
     printf("listening on port 29493, fd: %d\n", srv_sock_fd);
  }

  struct sockaddr_in client_address;
  socklen_t client_address_len = 0;
  server_fd = accept(srv_sock_fd, (struct sockaddr *)&client_address, &client_address_len);
  
  // Returning file descriptor value in fd
  printf("Connected client: %d\n", server_fd);
}

/**
 * [start_client description]
 * @return [description]
 */
int start_client(){
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_fd < 0)
  {
    printf("client socket() error\n");
    return sock_fd;
  }

  struct sockaddr_in sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(29493);

  const char* server_name = "localhost";
  inet_pton(AF_INET, server_name, &sa.sin_addr);

  if( connect(sock_fd, (struct sockaddr*)&sa, sizeof(sa)) != 0)
  {
    printf("Connect error\n");
    close(sock_fd);
    return -1;
  }

  return sock_fd;
}

/**
 * [main description]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char * argv[]){
  pthread_t thread_id;

  if( pthread_create(&thread_id, NULL, &start_server, NULL) != 0)
    printf("pthread_create error\n");

  sleep(2);

  int client_fd = start_client();
  printf("Client fd: %d\n", client_fd);
  printf("Server fd: %d\n", server_fd);

  sleep(10);

  close(client_fd);
  close(server_fd);



  return 0;
}
