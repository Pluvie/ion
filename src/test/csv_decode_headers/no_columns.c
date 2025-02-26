test( csv_decode_headers, no_columns ) {

  given("a csv file");
    char* csv_file;
    struct csv_properties csv = {
      .separator = ';',
      .wrapper = 0,
      .columns_count = 7,
      .encoding = UTF_8,
    };


  when("the file has no columns in the header row");
    csv_file = "\n"
      "abc;def\n";


  calling("csv_decode_headers()");
    struct memory allocator = memory_init(0);
    struct io input = io_reader(csv_file, strlen(csv_file));
    struct vector* headers = csv_decode_headers(&input, &allocator, csv);


  must("fail to decode the headers");
    verify(error.occurred == true);
    verify(headers == NULL);
    verify(streq(error.message, "expected a csv with at least one column"));


  success();
    memory_release(&allocator);
}
