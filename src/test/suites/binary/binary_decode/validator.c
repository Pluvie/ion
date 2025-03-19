#include "validator_functions.c"

test( binary_decode, validator ) {

  given("an example struct");
    struct example {
      u16 age;
      struct array numbers;
    } example;


  when("it has an associated reflection");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(age, U16, struct example), valid_if(is_adult) },
        { field(numbers, ARRAY, struct example), of({ type(I32) }),
          valid_if(all_numbers_greater_than_zero) },
      })
    };


  when("some input data is ready to decode");
    byte invalid_age_input[] = {
      0x03, 0x00,                                           /* example.age */
      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* numbers length */
      0x10, 0x00, 0x00, 0x00,                               /* numbers.0 */
      0x11, 0x00, 0x00, 0x00,                               /* numbers.1 */
      0x12, 0x00, 0x00, 0x00,                               /* numbers.2 */
    };

    byte invalid_numbers_input[] = {
      0x30, 0x00,                                           /* example.age */
      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* numbers length */
      0x20, 0x00, 0x00, 0x00,                               /* numbers.0 */
      0xff, 0xff, 0xff, 0xff,                               /* numbers.1 */
      0x22, 0x00, 0x00, 0x00,                               /* numbers.2 */
    };

    byte valid_input[] = {
      0x20, 0x00,                                           /* example.age */
      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* numbers length */
      0x10, 0x00, 0x00, 0x00,                               /* numbers.0 */
      0x11, 0x00, 0x00, 0x00,                               /* numbers.1 */
    };

    struct memory allocator = memory_init(4096);

    struct io valid_source = io_open_memory(
      valid_input, sizeof(valid_input));
    struct io invalid_age_source = io_open_memory(
      invalid_age_input, sizeof(invalid_age_input));
    struct io invalid_numbers_source = io_open_memory(
      invalid_numbers_input, sizeof(invalid_numbers_input));


  calling("binary_decode()");
  must("decode the input data based on the validator");
    binary_decode(&example, &valid_source, &rfx, &allocator);
    verify(error.occurred == false);

    binary_decode(&example, &invalid_age_source, &rfx, &allocator);
    verify(error.occurred == true);
    verify(streq(error.message,
      "[age] must be greater or equal than 18"));
    error_reset();

    binary_decode(&example, &invalid_numbers_source, &rfx, &allocator);
    verify(error.occurred == true);
    verify(streq(error.message,
      "[numbers] all numbers must be greater than 0"));
    error_reset();


  success();
    memory_release(&allocator);
}
