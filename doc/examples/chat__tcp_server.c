#include "../../src/ion.h"
#include "../../src/ion.c"
void chat_responder (struct tcp_server* server);

/**
 * This program illustrates how to use ⚡️ION⚡️ to build a simple TCP server chat.
 *
 * The server shall listen for incoming connections and relay back to the client the
 * received messages. Upon receiving the "quit" message, the server shall close the
 * connection and begin accpeting a new one. */

i32 main (
    i32 argc,
    char** argv
)
{
  /* Defines a TCP server listening on all incoming IPs (0.0.0.0) on port 7000,
   * using the `chat_responder` function to handle an accepted new connection. */
  struct tcp_server server = {
    .ip = "0.0.0.0",
    .port = 7000,
    .connector = chat_responder,
  };

  print("Starting server.");
  tcp_server_start(&server);
  print("Server stopped.");

  return EXIT_SUCCESS;
}

/**
 * This function shall handle a new accepted connection from a client.
 *
 * The client shall send arbitrary messages, and this function shall relay back the
 * received message: just like a mountain echo. */
void chat_responder (
    struct tcp_server* server
)
{
  print("New connection from: %s.", server->client_ip);
  print("Waiting for messages.");

  /* The io abstraction is a common interface to execute input / output operations
   * on various devices. In this case, a network socket. */
  struct io reader = io_open_socket(server->descriptor);
  struct io writer = io_open_socket(server->descriptor);

  char* message = NULL;
  char reply[2048] = { 0 };

read_message:
  message = io_read(&reader, 2048);

  /* The client sent 0 bytes: this happens if the client crashes or either way closes
   * the connection. We can safely close the connection on our end too. */
  if (reader.read_amount == 0)
    goto close_connection;

  /* There was an error while receiving the client message: we print it on screen and
   * close the connection. We could also have tried a new read. The important thing is
   * to always check for errors when doing IO operations. */
  if (error.occurred) {
    print("Error while reading client message: %s", error.message);
    goto close_connection;
  }

  /* The client sent a "quit" message. We respond with "Bye" and close the connection. */
  if (streq("quit", message)) {
    io_write(&writer, "Bye", sizeof("Bye"));
    /* Skipping error check since we do not care if the client actually receives the
     * goodbye message as we are going to close the connection anyway. */
    goto close_connection;
  }

  print("Received: %s.", message);
  snprintf(reply, sizeof(reply), "You sent: %s.", message);

  /* Send back the reply to the client. */
  io_write(&writer, reply, sizeof(reply));
  if (error.occurred) {
    print("Error while sending reply to the client: %s", error.message);
  }

  /* Read the next message! */
  goto read_message;

close_connection:
  /* Closes the IOs and release their buffers. */
  io_close(&reader);
  io_close(&writer);

  if (server->descriptor > 0)
    close(server->descriptor);
}
