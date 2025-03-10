#include "../../src/ion/modules/core.h"
#include "../../src/ion/modules/io.h"
#include "../../src/ion/modules/tcp.h"
#include "../../src/ion/modules/core.c"
#include "../../src/ion/modules/io.c"
#include "../../src/ion/modules/tcp.c"
void chat_sender (struct tcp_client* client);

/**
 * This program illustrates how to use ⚡️ION⚡️ to build a simple TCP client chat.
 *
 * The client shall connect to a specified IP and port, and present the user a text
 * prompt. The inserted message shall be sent to the server, and a reply shall be
 * read.
 *
 * Upon reading the "quit" message, the connection to the server shall be closed and
 * the client shall terminate its execution. */

i32 main (
    i32 argc,
    char** argv
)
{
  /* Defines a TCP client connecting on the local machine (127.0.0.1) to the port
   * 7000. */
  struct tcp_client client = {
    .ip = "127.0.0.1",
    .port = 7000,
  };

  /* Starts the client: should any error occur, the client must be considered invalid. */
  tcp_client_start(&client);
  if (error.occurred) {
    print("Could not connect to server: %s", error.message);
    return EXIT_FAILURE;
  }

  /* Shows the text prompt to the user. When the user types "quit", the client shall
   * terminate. */
  print("Starting client. Type `quit` to exit.");
  chat_sender(&client);
  print("Client stopped.");

  return EXIT_SUCCESS;
}

/**
 * This function shall gather the text message that the user inserts via prompt. It
 * shall then send it to the server and read back its reply.
 *
 * This process repeats until the user types "quit". */
void chat_sender (
    struct tcp_client* client
)
{
  /* This string holds the text that the user inserts via prompt. */
  char prompt[1024] = { 0 };

  /* The io abstraction is a common interface to execute input / output operations
   * on various devices. In this case, a network socket. */
  struct io reader = io_open_socket(client->descriptor);
  struct io writer = io_open_socket(client->descriptor);

send_messages:
  while(streq("quit", prompt) == false) {
    /* Shows a fancy prompt. */
    emit_c(PRINT_COLOR_CYAN, "> ");
    /* A zero length prompt means that the user has sent EOF (Ctrl+D). In this case
     * we close the client, but we could also have showed the prompt again. */
    if (fgets(prompt, sizeof(prompt), stdin) == NULL)
      break;

    /* Remove trailing newline. */
    prompt[strcspn(prompt, "\r\n")] = 0;

    /* Sends the text message to the server. If a network error occurs, print it on
     * screen and close the client. */
    io_write(&writer, prompt, sizeof(prompt));
    if (error.occurred) {
      print("Error while sending message: %s", error.message);
      break;
    }

    /* Reads back the server reply. If a network error occurs, print it on screen and
     * close the client. */
    char* reply = io_read(&reader, 2048);
    if (error.occurred) {
      print("Error while receiving server reply: %s", error.message);
      break;
    }

    /* Print the server reply and start the prompt again! */
    print("%s", reply);
  }

close_connection:
  /* Closes the IOs and release their buffers. */
  io_close(&reader);
  io_close(&writer);

  /* Close the client socket, if not already done by a previous system call. */
  if (client->descriptor > 0)
    close(client->descriptor);
}
