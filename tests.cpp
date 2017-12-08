#include "catch.hpp"

#include "sockserver.h"

#include <unistd.h>

TEST_CASE( "fds received", "[factorial]" ) {
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