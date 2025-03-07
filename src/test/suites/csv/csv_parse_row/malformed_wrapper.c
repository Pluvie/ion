test( csv_parse_row, malformed_wrapper ) {

  given("multiple csv rows with a malformed wrapper");
    char* rows =
      "a,sample,row\n"
      "\"ano\"ther,sample,row\n"
      "yet another,sample,row\n"
      "\"and \"finally,last,one\n";


  when("the csv properties have the comma as separator and a wrapper");
    struct csv_properties csv = {
      .separator = ',',
      .wrapper = '"',
      .columns_count = 3,
      .encoding = UTF_8,
    };


  calling("csv_parse_row() in succession");
    struct memory allocator = memory_init(0);
    struct io rows_io = io_open_memory(rows, strlen(rows));
    struct array* fields_1 = csv_parse_row(&rows_io, &allocator, csv);
    struct array* fields_2 = csv_parse_row(&rows_io, &allocator, csv);


  must("fail to parse the fields");
    verify(error.occurred == true);
    verify(fields_1 != NULL);
    verify(fields_1->length == csv.columns_count);
    verify(fields_2 == NULL);
    verify(streq(error.message,
      "expected separator `,`, or newline, after wrapper `\"`, at position 19:\n"
      "a,sample,row\n"
      "\"ano\"ther,sample,row\n"
      "      ^"));


  success();
    memory_release(&allocator);
}
