<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## I/O

__Ion__ offers a set of functions to normalize common input / output operations.

Usually input / output is done over three channels:

  - Memory: reading and writing data directly on address spaces.
  - File: reading and writing data to streams on the hard drive.
  - Network: reading and writing data to various type of sockets.

In any event, all these channels have a common paradigm which is that the fundamental
data being passed are bytes and those bytes have a fixed length.

This allows us to abstract these channels and offer only two functions to work with
i/o:

  - `io_read(struct io*, u64 amount)`
  - `io_write(struct io*, void* data, u64 amount)`

What controls the channel is the `struct io` object passed to these functions. Depending
on the channel there are three macros to create it:

  - `io_reader(void* data, u64 length)` for a reader on the memory.
  - `io_reader_file(void* stream, u64 length)` for a reader on a file.
  - `io_reader_socket(i32 socket, struct buffer* allocator)` for a reader on a socket.
  - `io_writer(void* data, u64 length, ...allocator)` for a writer on the memory.
  - `io_writer_file(void* stream)` for a writer on a file.
  - `io_writer_socket(i32 socket)` for a writer on a socket.

All i/o operations can fail: it is mandatory to check the `error` in order to avoid
inconsistencies in data, or worse, segmentation faults:

```c
byte[] data = { 7, 8, 9 };

struct io reader = io_reader(data, sizeof(data));
void* result = io_read(&reader, 3);
/* No error and result holds a pointer to { 7, 8, 9 }. */

result = io_read(&reader, 3);
/* Error: io is exhausted. Result is not a valid pointer. */
if (error.occurred)
  print("Unable to read from memory: %s", error.message);
```
