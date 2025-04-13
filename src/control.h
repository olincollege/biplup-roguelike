#pragma once

// STRUCTS
// Group the data needed for a server to run.
typedef struct {
  /// The socket descriptor to listen for connections.
  int listener;
  /// The address and port for the listener socket.
  struct sockaddr_in addr;
  /// The maximum number of clients that can be waiting to connect at once.
  int max_backlog;
} echo_server;

// FUNCTION DESCRIPTORS

/**
 * Read and echo lines from a client socket until the end of the file.
 *
 * Given a socket descriptor corresponding to to a connected client, read lines
 * from the given socket, echoing them back on the same socket as each line is
 * read. Continue this process until the client sends an EOF marker or until an
 * error is encountered. Upon EOF, close the file and exit. Upon an error at
 * any point, print an error message and terminate the program, in which case
 * the function does not return.
 *
 * @param socket_descriptor The socket descriptor for the client connection.
 */
void echo(int socket_descriptor);
