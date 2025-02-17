#include "test/array_get/element_at_position.c"
#include "test/array_get/position_out_of_bounds.c"
#include "test/array_init/default_capacity.c"
#include "test/array_init/immediate_allocation.c"
#include "test/array_init/power_2_capacity.c"
#include "test/binary_decode/array.c"
#include "test/binary_decode/array_maxlength.c"
#include "test/binary_decode/array_minlength.c"
#include "test/binary_decode/pointer.c"
#include "test/binary_decode/primitive.c"
#include "test/binary_decode/sequence.c"
#include "test/binary_decode/validator.c"
#include "test/binary_decode/vector.c"
#include "test/binary_decode/vector_maxlength.c"
#include "test/binary_decode/vector_minlength.c"
#include "test/binary_encode/array.c"
#include "test/binary_encode/pointer.c"
#include "test/binary_encode/primitive.c"
#include "test/binary_encode/sequence.c"
#include "test/binary_encode/vector.c"
#include "test/binary_protocol/round_trip.c"
#include "test/buffer_alloc/address_unreliability.c"
#include "test/buffer_alloc/data_consistency.c"
#include "test/buffer_alloc/dynamic_grow_double_cap.c"
#include "test/buffer_alloc/dynamic_grow_next_pow_2.c"
#include "test/buffer_alloc/first_alloc_aligned.c"
#include "test/buffer_alloc/increment_position.c"
#include "test/buffer_init/default_capacity.c"
#include "test/buffer_init/no_immediate_allocation.c"
#include "test/buffer_init/power_2_capacity.c"
#include "test/io_read_memory/invalid_cursor.c"
#include "test/io_read_memory/valid_cursor.c"
#include "test/io_read_socket/recv_failure.c"
#include "test/io_read_socket/recv_partial.c"
#include "test/io_read_socket/recv_success.c"
//#include "test/json_decode_number/convert_error.c"
//#include "test/json_decode_number/parse_error.c"
//#include "test/json_decode_number/success.c"
//#include "test/json_decode_struct/success.c"
//#include "test/json_parse_number/error_eof.c"
//#include "test/json_parse_number/error_exponent.c"
//#include "test/json_parse_number/error_exponent_eof.c"
//#include "test/json_parse_number/error_hex.c"
//#include "test/json_parse_number/error_mantissa.c"
//#include "test/json_parse_number/error_mantissa_eof.c"
//#include "test/json_parse_number/error_oct.c"
//#include "test/json_parse_number/exponent.c"
//#include "test/json_parse_number/exponent_negative.c"
//#include "test/json_parse_number/integer.c"
//#include "test/json_parse_number/integer_negative.c"
//#include "test/json_parse_number/mantissa.c"
//#include "test/json_parse_number/mantissa_negative.c"
//#include "test/json_parse_string/correct.c"
//#include "test/json_parse_string/escaped_double_quote.c"
//#include "test/json_parse_string/escaped_other.c"
//#include "test/json_parse_string/incorrect.c"
//#include "test/json_parse_string/unterminated.c"
#include "test/map_get/value_at_key.c"
#include "test/map_init/default_capacity.c"
#include "test/map_init/immediate_allocation.c"
#include "test/map_init/power_2_capacity.c"
#include "test/map_rehash/data_invariance.c"
#include "test/map_rehash/doubled_capacity.c"
#include "test/map_set/rehash_trigger.c"
#include "test/memory_alloc/dynamic_grow_double_cap.c"
#include "test/memory_alloc/dynamic_grow_next_pow_2.c"
#include "test/memory_alloc/first_alloc_aligned.c"
#include "test/memory_alloc/increment_position.c"
#include "test/memory_alloc_zero/zero_out.c"
#include "test/memory_init/default_capacity.c"
#include "test/memory_init/no_immediate_allocation.c"
#include "test/memory_init/power_2_capacity.c"
#include "test/reflect_failure/preserve_trace.c"
#include "test/reflect_path_print/dot_separated.c"
#include "test/reflect_path_print/empty.c"
#include "test/reflect_path_print/index.c"
#include "test/sci_notation_convert/decimal_128.c"
#include "test/sci_notation_convert/decimal_32.c"
#include "test/sci_notation_convert/decimal_64.c"
#include "test/sci_notation_convert/integer_consistency_exponent.c"
#include "test/sci_notation_convert/integer_consistency_mantissa.c"
#include "test/sci_notation_convert/signed_16.c"
#include "test/sci_notation_convert/signed_16_overflow.c"
#include "test/sci_notation_convert/signed_16_underflow.c"
#include "test/sci_notation_convert/signed_32.c"
#include "test/sci_notation_convert/signed_32_overflow.c"
#include "test/sci_notation_convert/signed_32_underflow.c"
#include "test/sci_notation_convert/signed_64.c"
#include "test/sci_notation_convert/signed_64_overflow.c"
#include "test/sci_notation_convert/signed_64_underflow.c"
#include "test/sci_notation_convert/signed_8.c"
#include "test/sci_notation_convert/signed_8_overflow.c"
#include "test/sci_notation_convert/signed_8_underflow.c"
#include "test/sci_notation_convert/type_not_numeric.c"
#include "test/sci_notation_convert/unsigned_16.c"
#include "test/sci_notation_convert/unsigned_16_overflow.c"
#include "test/sci_notation_convert/unsigned_32.c"
#include "test/sci_notation_convert/unsigned_32_overflow.c"
#include "test/sci_notation_convert/unsigned_64.c"
#include "test/sci_notation_convert/unsigned_64_overflow.c"
#include "test/sci_notation_convert/unsigned_8.c"
#include "test/sci_notation_convert/unsigned_8_overflow.c"
#include "test/sci_notation_convert/unsigned_consistency.c"
#include "test/tensor_at/correct_offsets.c"
#include "test/tensor_at_ranges/correct_offsets.c"
#include "test/tensor_at_sequences/correct_offsets.c"
#include "test/tensor_init/correct_dimensions.c"
#include "test/tensor_init/correct_length.c"
#include "test/tensor_init/correct_offsets.c"
#include "test/tensor_iterate_ranges/correct_positions.c"
#include "test/tensor_iterate_sequences/correct_positions.c"
#include "test/vector_get/element_at_position.c"
#include "test/vector_get/position_out_of_bounds.c"
#include "test/vector_init/correct_length.c"

void test_suite (
    void
)
{
  test_run( array_get, element_at_position );
  test_run( array_get, position_out_of_bounds );
  test_run( array_init, default_capacity );
  test_run( array_init, immediate_allocation );
  test_run( array_init, power_2_capacity );
  test_run( binary_decode, array );
  test_run( binary_decode, array_maxlength );
  test_run( binary_decode, array_minlength );
  test_run( binary_decode, pointer );
  test_run( binary_decode, primitive );
  test_run( binary_decode, sequence );
  test_run( binary_decode, validator );
  test_run( binary_decode, vector );
  test_run( binary_decode, vector_maxlength );
  test_run( binary_decode, vector_minlength );
  test_run( binary_encode, array );
  test_run( binary_encode, pointer );
  test_run( binary_encode, primitive );
  test_run( binary_encode, sequence );
  test_run( binary_encode, vector );
  test_run( binary_protocol, round_trip );
  test_run( buffer_alloc, address_unreliability );
  test_run( buffer_alloc, data_consistency );
  test_run( buffer_alloc, dynamic_grow_double_cap );
  test_run( buffer_alloc, dynamic_grow_next_pow_2 );
  test_run( buffer_alloc, first_alloc_aligned );
  test_run( buffer_alloc, increment_position );
  test_run( buffer_init, default_capacity );
  test_run( buffer_init, no_immediate_allocation );
  test_run( buffer_init, power_2_capacity );
  test_run( io_read_memory, invalid_cursor );
  test_run( io_read_memory, valid_cursor );
  test_run( io_read_socket, recv_failure );
  test_run( io_read_socket, recv_partial );
  test_run( io_read_socket, recv_success );
  //test_run( json_decode_number, convert_error );
  //test_run( json_decode_number, parse_error );
  //test_run( json_decode_number, success );
  //test_run( json_decode_struct, success );
  //test_run( json_parse_number, error_eof );
  //test_run( json_parse_number, error_exponent );
  //test_run( json_parse_number, error_exponent_eof );
  //test_run( json_parse_number, error_hex );
  //test_run( json_parse_number, error_mantissa );
  //test_run( json_parse_number, error_mantissa_eof );
  //test_run( json_parse_number, error_oct );
  //test_run( json_parse_number, exponent );
  //test_run( json_parse_number, exponent_negative );
  //test_run( json_parse_number, integer );
  //test_run( json_parse_number, integer_negative );
  //test_run( json_parse_number, mantissa );
  //test_run( json_parse_number, mantissa_negative );
  //test_run( json_parse_string, correct );
  //test_run( json_parse_string, escaped_double_quote );
  //test_run( json_parse_string, escaped_other );
  //test_run( json_parse_string, incorrect );
  //test_run( json_parse_string, unterminated );
  test_run( map_get, value_at_key );
  test_run( map_init, default_capacity );
  test_run( map_init, immediate_allocation );
  test_run( map_init, power_2_capacity );
  test_run( map_rehash, data_invariance );
  test_run( map_rehash, doubled_capacity );
  test_run( map_set, rehash_trigger );
  test_run( memory_alloc, dynamic_grow_double_cap );
  test_run( memory_alloc, dynamic_grow_next_pow_2 );
  test_run( memory_alloc, first_alloc_aligned );
  test_run( memory_alloc, increment_position );
  test_run( memory_alloc_zero, zero_out );
  test_run( memory_init, default_capacity );
  test_run( memory_init, no_immediate_allocation );
  test_run( memory_init, power_2_capacity );
  test_run( reflect_failure, preserve_trace );
  test_run( reflect_path_print, dot_separated );
  test_run( reflect_path_print, empty );
  test_run( reflect_path_print, index );
  test_run( sci_notation_convert, decimal_128 );
  test_run( sci_notation_convert, decimal_32 );
  test_run( sci_notation_convert, decimal_64 );
  test_run( sci_notation_convert, integer_consistency_exponent );
  test_run( sci_notation_convert, integer_consistency_mantissa );
  test_run( sci_notation_convert, signed_16 );
  test_run( sci_notation_convert, signed_16_overflow );
  test_run( sci_notation_convert, signed_16_underflow );
  test_run( sci_notation_convert, signed_32 );
  test_run( sci_notation_convert, signed_32_overflow );
  test_run( sci_notation_convert, signed_32_underflow );
  test_run( sci_notation_convert, signed_64 );
  test_run( sci_notation_convert, signed_64_overflow );
  test_run( sci_notation_convert, signed_64_underflow );
  test_run( sci_notation_convert, signed_8 );
  test_run( sci_notation_convert, signed_8_overflow );
  test_run( sci_notation_convert, signed_8_underflow );
  test_run( sci_notation_convert, type_not_numeric );
  test_run( sci_notation_convert, unsigned_16 );
  test_run( sci_notation_convert, unsigned_16_overflow );
  test_run( sci_notation_convert, unsigned_32 );
  test_run( sci_notation_convert, unsigned_32_overflow );
  test_run( sci_notation_convert, unsigned_64 );
  test_run( sci_notation_convert, unsigned_64_overflow );
  test_run( sci_notation_convert, unsigned_8 );
  test_run( sci_notation_convert, unsigned_8_overflow );
  test_run( sci_notation_convert, unsigned_consistency );
  test_run( tensor_at, correct_offsets );
  test_run( tensor_at_ranges, correct_offsets );
  test_run( tensor_at_sequences, correct_offsets );
  test_run( tensor_init, correct_dimensions );
  test_run( tensor_init, correct_length );
  test_run( tensor_init, correct_offsets );
  test_run( tensor_iterate_ranges, correct_positions );
  test_run( tensor_iterate_sequences, correct_positions );
  test_run( vector_get, element_at_position );
  test_run( vector_get, position_out_of_bounds );
  test_run( vector_init, correct_length );
}
