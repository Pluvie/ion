test( json_parse_string, buffer_optimization ) {

  given("a json string");
    char* json = "\"example string\"";


  when("the string is read from a file");
    void* file = fopen("src/test/json_parse_string/buffer_optimization.txt", "r");
    struct io input = io_reader_file(file);


  calling("json_parse_string()");
    u64 string_length = json_parse_string(&input);


  must("parse the string correctly and optimize the number of reads");
    verify(error.occurred == false);
    verify(string_length == strlen(json));
    verify(input.reads_count == 1);


  success();
    fclose(file);
}
