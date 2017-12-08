#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char * argv[]){
  int listen_sock_fd = socket(PF_INET, SOCK_STREAM, 0);
  if(listen_sock_fd < 0)
  {
    printf("socket() error");
    return -1;
  }

  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8989);
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((bind(listen_sock_fd, (struct sockaddr *)&server_address, sizeof(server_address))) < 0) {
     printf("bind() error");
     return -2;
  }

  int wait_size = 2;  // maximum number of waiting clients
  if (listen(listen_sock_fd, wait_size) < 0) {
     printf("listen() error\n");
     return -3;
  }

  return 0;
}
