test( json_parse_string, buffer_optimization_file ) {

  given("a json string");
    char json[] = "\"example string\"";


  when("the string is read from a file");
    fread_simulated_data = &io_reader(json, sizeof(json));
    struct io input = {
      .channel = IO_CHANNEL_FILE,
      .mode = IO_MODE_READ,
      .length = sizeof(json),
    };


  calling("json_parse_string()");
    u64 string_length = json_parse_string(&input);


  must("parse the string correctly and optimize the number of reads");
    verify(error.occurred == false);
    verify(string_length == strlen(json));
    verify(input.reads_count == 1);


  success();
}
