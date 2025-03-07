test( csv_decode_headers, unmatching_fields ) {

  given("a csv file");
    char* csv_file =
      "Esculapio,33,1-jan-99\n"
      "Romualdo,17,31-dec-99\n";


  when("it has an associated reflection");
    struct array users;

    struct user {
      struct string name;
      struct string last_login;
      u32 age;
    };

    struct reflection rfx = {
      type(ARRAY), of({
        type(STRUCT, struct user), fields({
          { field(name, STRING, struct user), named("USERNAME") },
          { field(age, U32, struct user), named("AGE") },
        })
      })
    };


  when("the csv properties have the comma as separator");
    struct csv_properties csv = {
      .separator = ',',
      .wrapper = '\0',
      .columns_count = 3,
      .encoding = UTF_8,
    };


  calling("csv_decode_headers()");
    struct memory allocator = memory_init(0);
    struct io csv_io = io_open_memory(csv_file, strlen(csv_file));
    reflection_initialize(&rfx, &users, &allocator);
    struct array* headers = csv_decode_headers(&csv_io, rfx.element, csv);


  must("sequentially match the fields");
    verify(error.occurred == false);
    verify(headers != NULL);
    verify(headers->length == csv.columns_count);

    struct reflection** header;
    struct reflection* field_rfx;

    header = array_get(headers, 0);
    field_rfx = vector_get(rfx.element->fields, 0);
    verify(*header != NULL);
    verify(*header == field_rfx);

    header = array_get(headers, 1);
    field_rfx = vector_get(rfx.element->fields, 1);
    verify(*header != NULL);
    verify(*header == field_rfx);

    header = array_get(headers, 2);
    verify(*header == NULL);


  success();
    memory_release(&allocator);
}
