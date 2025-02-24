test( error_add_io_extraction, position_only ) {

  given("some input data");
    char* input =
      "{"                                     "\n"
      "  \"number\": 255,"                    "\n"
      "  \"example_string\": \"example\","    "\n"
      "}";


  when("it has an associated io");
    struct io source = io_reader(input, strlen(input));


  when("the io has encountered an error afer reading some data");
    source.cursor = 14;
    fail("unexpected io error");


  when("the io cannot be extracted");
    source.channel = IO_CHANNEL_SOCK;


  calling("error_add_io_extraction()");
    error_add_io_extraction(&source);


  must("set the error message with the correct position and without a data extraction");
    verify(error.occurred == true);
    char* expected_error_message = "unexpected io error, at position 14";
    verify(streq(error.message, expected_error_message));

    verify(streq(error.trace[0].file,
      "./src/test/error_add_io_extraction/position_only.c"));
    verify(error.trace[0].line == 17);


  success();
}
