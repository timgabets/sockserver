#include "include/catch.hpp"
#include "include/sockserver.h"

#include <unistd.h>

TEST_CASE( "should receive file descriptors", "" ) {
  int server_fd = -1;
  int client_fd = -1;

  getFDs(&server_fd, &client_fd);
  
  REQUIRE( server_fd != -1 );
  REQUIRE( client_fd != -1 );
  REQUIRE( server_fd > 0 );
  REQUIRE( client_fd > 0 );

  close(server_fd);
  close(client_fd);
}

TEST_CASE( "5 consecutive calls should receive should be succsessfull", "" ) {
  for(int i =0; i < 5; i++){
    int server_fd = -1;
    int client_fd = -1;

    getFDs(&server_fd, &client_fd);
  
    REQUIRE( server_fd != -1 );
    REQUIRE( client_fd != -1 );
    REQUIRE( server_fd > 0 );
    REQUIRE( client_fd > 0 );

    close(server_fd);
    close(client_fd);
  }
}
