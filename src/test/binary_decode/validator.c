#include "validator_functions.c"

test( binary_decode, validator ) {

  given("an example struct");
    struct example {
      u16 age;
      struct array numbers;
    } example;


  when("it has an associated reflection");
    struct reflect reflection = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, age), type(U16), valid_if(is_adult) },
        { field(struct example, numbers), type(ARRAY), of({ type(I32) }),
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
    struct object target = object(example, &reflection, &allocator);

    struct io valid_source = io_memory(
      valid_input, sizeof(valid_input));
    struct io invalid_age_source = io_memory(
      invalid_age_input, sizeof(invalid_age_input));
    struct io invalid_numbers_source = io_memory(
      invalid_numbers_input, sizeof(invalid_numbers_input));


  calling("binary_decode()");
  must("decode the input data based on the validator");
    binary_decode(&valid_source, &target);
    verify(error.occurred == false);

    binary_decode(&invalid_age_source, &target);
    verify(error.occurred == true);
    verify(streq(error.message,
      "[age] must be greater or equal than 18"));
    error_reset();

    binary_decode(&invalid_numbers_source, &target);
    verify(error.occurred == true);
    verify(streq(error.message,
      "[numbers] all numbers must be greater than 0"));
    error_reset();


  success();
    memory_release(&allocator);
}
