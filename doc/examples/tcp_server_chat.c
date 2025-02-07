#include "ion.h"
#include "ion.c"

void chat_responder (
    struct tcp_server* server
)
{
  struct buffer allocator = buffer_init(0);
  struct io reader = io_reader_socket(server->descriptor, &allocator);

  char* message = io_read(&reader, 1024);
  char reply[1024] = { 0 };
  snprintf(reply, sizeof(reply), "You sent: %s.", message);

  struct io writer = io_writer_socket(server->descriptor);
  io_write(&writer, reply, sizeof(reply));

  close(server->descriptor);
}

i32 main (
    i32 argc,
    char** argv
)
{
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
