#include "ion.h"
#include "ion.c"

void chat_sender (
    struct tcp_client* client
)
{
  char buffer[1024] = { 0 };
  struct buffer allocator = buffer_init(0);

  struct io reader = io_reader_socket(client->descriptor, &allocator);
  struct io writer = io_writer_socket(client->descriptor);

  while(streq("quit", buffer) == false) {
    emit_c(PRINT_COLOR_CYAN, "> ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
      break;

    /* Remove trailing newline. */
    buffer[strcspn(buffer, "\r\n")] = 0;

    io_write(&writer, buffer, sizeof(buffer));
    if (error.occurred) {
      print("Error while sending message: %s", error.message);
      break;
    }

    char* reply = io_read(&reader, 2048);
    if (error.occurred) {
      print("Error while receiving server reply: %s", error.message);
      break;
    }
    print("%s", reply);
  }

  if (client->descriptor > 0)
    close(client->descriptor);

  buffer_release(&allocator);
}

i32 main (
    i32 argc,
    char** argv
)
{
  struct tcp_client client = {
    .ip = "127.0.0.1",
    .port = 7000,
  };

  tcp_client_start(&client);
  if (error.occurred) {
    print("Could not connect to server: %s", error.message);
    return EXIT_FAILURE;
  }

  print("Starting client. Type `quit` to exit.");
  chat_sender(&client);
  print("Client stopped.");

  return EXIT_SUCCESS;
}
