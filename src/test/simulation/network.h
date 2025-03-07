/**
 * This file simulates network sending / receiving, in order to control which
 * data is being transmitted. */




/**
 * In order to simulate received data, make this variable point to a `struct io` which
 * reads over a buffer of your desired data. Each `recv` call shall read on the buffer,
 * advancing its cursor, and returning the amount of bytes successfully read. */
struct io* recv_simulated_data = NULL;

/**
 * In order to simulate received data, make this variable point to a `struct io` which
 * writes on a buffer of your desired data. Each `send` call shall write on the buffer,
 * advancing its cursor, and returning the amount of bytes successfully written. */
struct io* send_simulated_data = NULL;




/**
 * Makes all functions that call `recv` to actually call `recv_simulated`. */
#define recv recv_simulated

/**
 * Makes all functions that call `send` to actually call `send_simulated`. */
#define send send_simulated




i64 recv_simulated (
    i32 connection,
    void* output,
    u64 length,
    i32 flags
)
/**
 * This function is a simulation of the real `recv` function, which enables to manually
 * specify the result of the recv call, and the received data.
 *
 * In order to do so, the global variable `recv_simulated_data` is used. Example:
 *
 * ```c
 * byte example_data[] = { 0x00, 0x01, 0x02 };
 * recv_simulated_data = &io_open_memory(example_data, sizeof(example_data));
 * ```
 *
 * Every time the `recv` function is invoked, the `recv_simulated_data` is read. */
{
  if (recv_simulated_data == NULL)
    return -1;

  if (io_exhausted(recv_simulated_data))
    return -1;

  i64 remainder = recv_simulated_data->length - recv_simulated_data->cursor;
  if (length > remainder)
    length = remainder;

  void* result = io_read(recv_simulated_data, length);

  if (flags & MSG_PEEK)
    recv_simulated_data->cursor -= recv_simulated_data->read_amount;

  if (error.occurred)
    return -1;

  memcpy(output, result, recv_simulated_data->read_amount);
  return length;
}

i64 send_simulated (
    i32 connection,
    const void* data,
    u64 length,
    i32 flags
)
/**
 * This function is a simulation of the real `send` function, which enables to manually
 * specify the result of the send call, and the sent data.
 *
 * In order to do so, the global variable `send_simulated_data` is used. Example:
 *
 * ```c
 * byte example_data[64] = { 0 };
 * send_simulated_data = &io_open_memory(example_data, sizeof(example_data));
 * ```
 *
 * Every time the `send` function is invoked, the `send_simulated_data` is written. */
{
  if (send_simulated_data == NULL)
    return -1;

  if (io_exhausted(send_simulated_data))
    return -1;

  u64 remainder = send_simulated_data->length - send_simulated_data->cursor;
  if (length > remainder)
    length = remainder;

  io_write(send_simulated_data, (void*) data, length);
  if (error.occurred)
    return -1;

  return length;
}
