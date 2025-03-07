test( csv_parse_row, comma_separated_overcount ) {

  given("a csv row with columns over the count");
    char* row = "a,sample,row,extra,columns\n";


  when("the csv properties have the comma as separator");
    struct csv_properties csv = {
      .separator = ',',
      .wrapper = '\0',
      .columns_count = 3,
      .encoding = UTF_8,
    };


  calling("csv_parse_row()");
    struct memory allocator = memory_init(0);
    struct io row_io = io_open_memory(row, strlen(row));
    struct array* fields = csv_parse_row(&row_io, &allocator, csv);


  must("fail to parse the fields");
    verify(error.occurred == true);
    verify(fields == NULL);
    verify(streq(error.message,
      "expected newline but found more than the specified 3 columns count, "
        "at position 13:\n"
      "a,sample,row,extra,columns\n"
      "            ^"));


  success();
    memory_release(&allocator);
}
