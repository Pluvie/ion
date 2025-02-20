test( json_parse_string, buffer_optimization_socket ) {

  given("a json string");
    char json[] = "\"example string\"";


  when("the string is read from a socket");
    recv_simulated_data = &io_reader(json, sizeof(json));
    struct io input = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  calling("json_parse_string()");
    u64 string_length = json_parse_string(&input);


  must("parse the string correctly and optimize the number of reads");
    verify(error.occurred == false);
    verify(string_length == strlen(json));
    verify(input.reads_count == 1);


  success();
}
