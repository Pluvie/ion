bool is_adult (
    void* age_ptr
)
{
  u16 age = *(u16*) age_ptr;
  if (age >= 18)
    return true;

  fail("must be greater or equal than 18");
  return false;
}

test( binary_decode, validator ) {

  given("an example struct");
    struct example {
      u16 age;
    } example;


  when("it has an associated schema")
    struct reflect schema = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, age), type(U16), valid_if(is_adult) },
      })
    };


  when("some input data is ready to decode");
    byte invalid_input[] = {
      0x03, 0x00,                                           /* example.age */
    };

    byte valid_input[] = {
      0x20, 0x00,                                           /* example.age */
    };


  when("a protocol decoder is set up on valid data");
    struct memory allocator = memory_init(4096);

    struct protocol valid_decoder = {
      .schema = &schema,
      .allocator = &allocator,
      .input = &io_reader(valid_input, sizeof(valid_input)),
      .output = &io_writer(&example, sizeof(example)),
    };

    struct protocol invalid_decoder = {
      .schema = &schema,
      .allocator = &allocator,
      .input = &io_reader(invalid_input, sizeof(invalid_input)),
      .output = &io_writer(&example, sizeof(example)),
    };


  calling("binary_decode()");
  must("decode the input data based on the validator");
    binary_decode(&valid_decoder);
    verify(error.occurred == false);

    binary_decode(&invalid_decoder);
    verify(error.occurred == true);
    verify(streq(error.message,
      "[age] must be greater or equal than 18"));

  success();
    error_reset();
    memory_release(&allocator);
}
