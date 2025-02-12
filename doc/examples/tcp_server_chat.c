#include "ion.h"
#include "ion.c"

struct buffer allocator;

void chat_responder (
    struct tcp_server* server
)
{
  print("New connection from: %s.", server->client_ip);
  print("Waiting for messages.");

  struct io reader = io_reader_socket(server->descriptor, &allocator);
  struct io writer = io_writer_socket(server->descriptor);

  char* message = NULL;
  char reply[2048] = { 0 };

read_message:
  message = io_read(&reader, 2048);

  if (reader.read_amount == 0)
    return;

  if (error.occurred) {
    print("Error while reading client message: %s", error.message);
    return;
  }

  if (streq("quit", message)) {
    io_write(&writer, "Bye", sizeof("Bye"));
    /* Skipping error check since we do not care if the client actually receives the
     * goodbye message as we are going to close the connection anyway. */
    return;
  }

  print("Received: %s.", message);
  snprintf(reply, sizeof(reply), "You sent: %s.", message);

  io_write(&writer, reply, sizeof(reply));
  if (error.occurred) {
    print("Error while sending reply to the client: %s", error.message);
  }

  goto read_message;
}

i32 main (
    i32 argc,
    char** argv
)
{
  allocator = buffer_init(0);

  struct tcp_server server = {
    .ip = "0.0.0.0",
    .port = 7000,
    .connector = chat_responder,
  };

  print("Starting server.");
  tcp_server_start(&server);
  print("Server stopped.");

  buffer_release(&allocator);

  return EXIT_SUCCESS;
}
