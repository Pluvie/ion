test( csv_parse_row, newline_unwrapped ) {

  given("a csv row with an unwrapped newline");
    char* row = "a,sam\nple,row\n";


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
    struct array* fields = csv_parse_row(&row_io, &allocator, &csv);


  must("correctly parse the row into the fields");
    verify(error.occurred == false);
    verify(fields != NULL);
    verify(fields->length == csv.columns_count);
    for array_each(fields, struct string*, field, field_index)
      switch (field_index) {
      case 0:
        verify(string_equal(field, &s("a")));
        continue;
      case 1:
        verify(string_equal(field, &s("sam\nple")));
        continue;
      case 2:
        verify(string_equal(field, &s("row")));
        continue;
      default:
        continue;
      }


  success();
    memory_release(&allocator);
}
