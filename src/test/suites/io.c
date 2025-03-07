#include "io.h"

void test_suite__io (
    void
)
{
  test_add( error_add_io_extraction, position_with_extraction );
  test_add( io_peek, restore_cursor );
  test_add( io_read_file, buffer_size );
  test_add( io_read_file, buffer_size_overflow );
  test_add( io_read_file, buffered_optimization );
  test_add( io_read_file, buffered_read );
  test_add( io_read_file, buffered_retention );
  test_add( io_read_file, buffered_retention_overflow );
  test_add( io_read_file, fread_failure );
  test_add( io_read_file, fread_partial );
  test_add( io_read_file, fread_success );
  test_add( io_read_memory, invalid_cursor );
  test_add( io_read_memory, valid_cursor );
  test_add( io_read_socket, buffer_size );
  test_add( io_read_socket, buffer_size_overflow );
  test_add( io_read_socket, buffered_optimization );
  test_add( io_read_socket, buffered_read );
  test_add( io_read_socket, buffered_retention );
  test_add( io_read_socket, buffered_retention_overflow );
  test_add( io_read_socket, recv_failure );
  test_add( io_read_socket, recv_partial );
  test_add( io_read_socket, recv_success );
  test_add( io_write_file, fwrite_failure );
  test_add( io_write_file, fwrite_success );
  test_add( io_write_memory, invalid_cursor );
  test_add( io_write_memory, valid_cursor );
  test_add( io_write_socket, send_failure );
  test_add( io_write_socket, send_success );
}
