#include "include/socketmock.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "errno.h"

typedef struct {
  int fd;
  int port;
  pthread_mutex_t mutex;
} shared_data;


/**
 * [start_server description]
 * @param arg [description]
 */
void* start_server(void* args){
  shared_data* data = (shared_data*) args;

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
    printf("server socket() error\n");
    pthread_mutex_unlock( &(data->mutex) );
    return NULL;
  }

  int enable = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    printf("setsockopt(SO_REUSEADDR) failed");

  struct sockaddr_in sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(data->port);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((bind(sockfd, (struct sockaddr *)&sa, sizeof(sa))) < 0) {
     printf("bind() error: %s\n", strerror(errno));
     pthread_mutex_unlock( &(data->mutex) );
     close(sockfd);
     return NULL;
  }

  int wait_size = 1;  // maximum number of waiting clients
  if (listen(sockfd, wait_size) < 0) {
     printf("server listen() error\n");
     pthread_mutex_unlock( &(data->mutex) );
     close(sockfd);
     return NULL;
  }

  struct sockaddr_in client_address;
  socklen_t client_address_len = 0;

  pthread_mutex_unlock( &(data->mutex) );
  data->fd = accept(sockfd, (struct sockaddr *)&client_address, &client_address_len);
 
  close(sockfd); 
  // Returning file descriptor value in fd  
  pthread_exit(NULL);
}

/**
 * [start_client description]
 * @return [description]
 */
int start_client(int port){
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_fd < 0)
  {
    printf("client socket() error\n");
    return sock_fd;
  }

  struct sockaddr_in sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);

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

void getFDs(const int port, int* server_fd, int* client_fd){
  pthread_t thread_id;
  shared_data data;
  data.port = port; 
  data.fd = -1914;
  pthread_mutex_init(&data.mutex, NULL);

  pthread_mutex_lock( &(data.mutex) );
  if( pthread_create(&thread_id, NULL, &start_server, &data) != 0)
  {
    printf("pthread_create error\n");
    return;
  }

  pthread_mutex_lock( &(data.mutex) );
  *client_fd = start_client(port);

  pthread_join(thread_id, NULL);
  *server_fd = data.fd;
}
