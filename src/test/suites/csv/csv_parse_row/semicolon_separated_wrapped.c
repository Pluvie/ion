test( csv_parse_row, semicolon_separated_wrapped ) {

  given("a csv row");
    char* row = "a;\"s\nample\";row\n";


  when("the csv properties have the semicolon as separator and a wrapper");
    struct csv_properties csv = {
      .separator = ';',
      .wrapper = '"',
      .columns_count = 3,
      .encoding = UTF_8,
    };


  calling("csv_parse_row()");
    struct memory allocator = memory_init(0);
    struct io row_io = io_open_memory(row, strlen(row));
    struct array* fields = csv_parse_row(&row_io, &allocator, csv);


  must("correctly parse the row into the fields");
    verify(error.occurred == false);
    verify(fields != NULL);
    verify(fields->length == csv.columns_count);
    for array_each_with_index(fields, field_index, struct string*, field)
      switch (field_index) {
      case 0:
        verify(streq("a", field->content));
        continue;
      case 1:
        verify(streq("s\nample", field->content));
        continue;
      case 2:
        verify(streq("row", field->content));
        continue;
      default:
        continue;
      }


  success();
    memory_release(&allocator);
}
