/**
 * This file simulates filesystem reading / writing, in order to control which
 * data is being operated. */




/**
 * In order to simulate read data, make this variable point to a `struct io` which
 * reads over a buffer of your desired data. Each `fread` call shall read on the buffer,
 * advancing its cursor, and returning the amount of bytes successfully read. */
struct io* fread_simulated_data = NULL;

/**
 * In order to simulate written data, make this variable point to a `struct io` which
 * writes on a buffer of your desired data. Each `fwrite` call shall write on the buffer,
 * advancing its cursor, and returning the amount of bytes successfully written. */
struct io* fwrite_simulated_data = NULL;




/**
 * Makes all functions that call `fread` to actually call `fread_simulated`. */
#define fread fread_simulated

/**
 * Makes all functions that call `fwrite` to actually call `fwrite_simulated`. */
#define fwrite fwrite_simulated

/**
 * Makes all functions that call `fseek` to actually call `fseek_simulated`. */
#define fseek fseek_simulated

/**
 * Makes all functions that call `ftell` to actually call `ftell_simulated`. */
#define ftell ftell_simulated




i32 fread_simulated (
    void* output,
    u64 byte_size,
    u64 count,
    void* stream
)
/**
 * This function is a simulation of the real `fread` function, which enables to manually
 * specify the result of the fread call, and the read data.
 *
 * In order to do so, the global variable `fread_simulated_data` is used. Example:
 *
 * ```c
 * byte example_data[] = { 0x00, 0x01, 0x02 };
 * fread_simulated_data = &io_open_memory(example_data, sizeof(example_data));
 * ```
 *
 * Every time the `fread` function is invoked, the `fread_simulated_data` is read. */
{
  if (fread_simulated_data == NULL)
    return 0;

  if (io_exhausted(fread_simulated_data))
    return 0;

  u64 total_size = count * byte_size;
  i64 remainder = fread_simulated_data->length - fread_simulated_data->cursor;
  if (total_size > remainder)
    total_size = remainder;

  void* result = io_read(fread_simulated_data, total_size);
  if (error.occurred)
    return 0;

  memcpy(output, result, fread_simulated_data->read_amount);
  if (total_size < byte_size)
    return 1;
  else
    return total_size / byte_size;
}

i32 fwrite_simulated (
    void* input,
    u64 byte_size,
    u64 count,
    void* stream
)
/**
 * This function is a simulation of the real `fwrite` function, which enables to manually
 * specify the result of the fwrite call, and the written data.
 *
 * In order to do so, the global variable `fwrite_simulated_data` is used. Example:
 *
 * ```c
 * byte example_data[64] = { 0 };
 * fwrite_simulated_data = &io_open_memory(example_data, sizeof(example_data));
 * ```
 *
 * Every time the `fwrite` function is invoked, the `fwrite_simulated_data` is written. */
{
  if (fwrite_simulated_data == NULL)
    return 0;

  if (io_exhausted(fwrite_simulated_data))
    return 0;

  u64 total_size = count * byte_size;
  i64 remainder = fwrite_simulated_data->length - fwrite_simulated_data->cursor;
  if (total_size > remainder)
    total_size = remainder;

  io_write(fwrite_simulated_data, input, total_size);
  if (error.occurred)
    return 0;

  if (total_size < byte_size)
    return 1;
  else
    return total_size / byte_size;
}

i32 fseek_simulated (
  void* stream,
  i64 offset,
  i32 whence
)
/**
 * This function is a simulation of the real `fseek` function, to avoid incorrect
 * NULL pointer access while simulating the filesystem, and to simulate correctly
 * the `io_peek_file` function. */
{
  if (fread_simulated_data == NULL)
    return -1;

  switch (whence) {
  case SEEK_SET:
    fread_simulated_data->cursor = offset;
    break;
  case SEEK_CUR:
    fread_simulated_data->cursor += offset;
    break;
  case SEEK_END:
    fread_simulated_data->cursor = fread_simulated_data->length - offset;
    break;
  }

  return 0;
}

i64 ftell_simulated (
  void* stream
)
/**
 * This function is a simulation of the real `ftell` function. */
{
  if (fread_simulated_data == NULL)
    return -1;

  return fread_simulated_data->cursor;
}
