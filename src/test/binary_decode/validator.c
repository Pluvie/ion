#include "./validator_functions.c"

test( binary_decode, validator ) {

  given("an example struct");
    struct example {
      u16 age;
      struct array numbers;
    } example;


  when("it has an associated schema")
    struct reflect schema = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, age), type(U16), valid_if(is_adult) },
        { field(struct example, numbers), type(ARRAY), of({ type(I32) }),
          valid_if(all_numbers_greater_than_zero) },
      })
    };


  when("some input data is ready to decode");
    byte invalid_input_age[] = {
      0x03, 0x00,                                           /* example.age */
      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* numbers length */
      0x10, 0x00, 0x00, 0x00,                               /* numbers.0 */
      0x11, 0x00, 0x00, 0x00,                               /* numbers.1 */
      0x12, 0x00, 0x00, 0x00,                               /* numbers.2 */
    };

    byte invalid_input_numbers[] = {
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


  when("a protocol decoder is set up on valid data");
    struct memory allocator = memory_init(4096);

    struct protocol valid_decoder = {
      .schema = &schema,
      .allocator = &allocator,
      .input = &io_reader(valid_input, sizeof(valid_input)),
      .output = &io_writer(&example, sizeof(example)),
    };

    struct protocol invalid_decoder_age = {
      .schema = &schema,
      .allocator = &allocator,
      .input = &io_reader(invalid_input_age, sizeof(invalid_input_age)),
      .output = &io_writer(&example, sizeof(example)),
    };

    struct protocol invalid_decoder_numbers = {
      .schema = &schema,
      .allocator = &allocator,
      .input = &io_reader(invalid_input_numbers, sizeof(invalid_input_numbers)),
      .output = &io_writer(&example, sizeof(example)),
    };


  calling("binary_decode()");
  must("decode the input data based on the validator");
    binary_decode(&valid_decoder);
    verify(error.occurred == false);

    binary_decode(&invalid_decoder_age);
    verify(error.occurred == true);
    verify(streq(error.message,
      "[age] must be greater or equal than 18"));
    error_reset();

    binary_decode(&invalid_decoder_numbers);
    verify(error.occurred == true);
    verify(streq(error.message,
      "[numbers] all numbers must be greater than 0"));
    error_reset();

  success();
    memory_release(&allocator);
}
