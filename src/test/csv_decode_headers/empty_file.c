test( csv_decode_headers, empty_file ) {

  given("a csv file");
    char* csv_file;
    struct csv_properties csv = {
      .separator = ';',
      .wrapper = 0,
      .columns_count = 7,
      .encoding = UTF_8,
    };


  when("the file is empty");
    csv_file = "";


  calling("csv_decode_headers()");
    struct memory allocator = memory_init(0);
    struct io input = io_reader(csv_file, strlen(csv_file));
    struct vector* headers = csv_decode_headers(&input, &allocator, csv);


  must("fail to decode the headers");
    verify(error.occurred == true);
    verify(headers == NULL);
    verify(streq(error.message, "csv is empty"));


  success();
    memory_release(&allocator);
}
