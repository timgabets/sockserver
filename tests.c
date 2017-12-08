#include "include/catch.hpp"
#include "include/sockserver.h"

#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int port = 19443;

TEST_CASE( "should receive file descriptors", "" ) {
  int server_fd = -1;
  int client_fd = -1;

  getFDs(port, &server_fd, &client_fd);
  
  REQUIRE( server_fd != -1 );
  REQUIRE( client_fd != -1 );
  REQUIRE( server_fd > 0 );
  REQUIRE( client_fd > 0 );

  close(server_fd);
  close(client_fd);
}


TEST_CASE( "should be able to exchange data with the given file descriptors", "" ) {
  int server_fd = -1;
  int client_fd = -1;
  
  getFDs(port, &server_fd, &client_fd);
  
  REQUIRE( server_fd != -1 );
  REQUIRE( client_fd != -1 );
  REQUIRE( server_fd > 0 );
  REQUIRE( client_fd > 0 );

  const char* send_buffer = "iddqd";
  send(client_fd, send_buffer, strlen(send_buffer), 0);

  char* recv_buffer[128] = {0};
  recv(server_fd, recv_buffer, 128, 0);

  REQUIRE( strcmp((const char*)recv_buffer, "iddqd") == 0 );

  close(server_fd);
  close(client_fd);
}

TEST_CASE( "5 consecutive calls should receive should be successfull", "" ) {
  for(int i =0; i < 5; i++){
    int server_fd = -1;
    int client_fd = -1;

    getFDs(port, &server_fd, &client_fd);
  
    REQUIRE( server_fd != -1 );
    REQUIRE( client_fd != -1 );
    REQUIRE( server_fd > 0 );
    REQUIRE( client_fd > 0 );

    close(server_fd);
    close(client_fd);
  }
}

