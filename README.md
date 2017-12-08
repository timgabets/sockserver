# sockserver

A simple utility to get the file descriptors of the listening TCP server and the TCP client connected to that server:

``` C++
int server_fd, client_fd;


// start the TCP server listening on 127.0.0.1:1337, 
// then connect the client to it and return the file descriptors:
getFDs(1337, &server_fd, &client_fd);

// client_fd is a file descriptor of the connected client, 
// so we can just send() data over it:
const char* send_buffer = "iddqd";
send(client_fd, send_buffer, strlen(send_buffer), 0);

// server_fd is a file descriptor of the server, which is ready for receiving data,
// so we can just read from socket using recv():
char* recv_buffer[128] = {0};
recv(server_fd, recv_buffer, 128, 0);

assert(strcmp((const char*)recv_buffer, "iddqd") == 0);
```

The utility may be useful for creating mocks in unit-test frameworks while testing network-related code.
