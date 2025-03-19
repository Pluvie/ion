test( csv_decode_row, field_types ) {

  given("a csv file");
    char* csv_file =
      "USERNAME,AGE,LAST_LOGIN\n"
      "Esculapio,33,1-jan-99\n"
      "Romualdo,17,31-dec-99\n";


  when("it has an associated reflection");
    struct user {
      struct string name;
      struct string last_login;
      u32 age;
    };

    struct reflection rfx = {
      type(ARRAY), of({
        type(STRUCT, struct user), fields({
          { field(age, U32, struct user), named("AGE") },
          { field(name, STRING, struct user), named("USERNAME") },
          { field(last_login, STRING, struct user), named("~~~~~") },
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
    struct reflection* row_rfx = rfx.element;
    row_rfx->support_data = &csv;


  when("the csv headers have been decoded");
    struct memory allocator = memory_init(0);
    struct io input = io_open_memory(csv_file, strlen(csv_file));
    csv_decode_headers(&input, row_rfx, &allocator);


  calling("csv_decode_row()");
    struct user user_1;
    row_rfx->index = 0;
    csv_decode_row(&user_1, &input, row_rfx, &allocator);

    struct user user_2;
    row_rfx->index = 0;
    csv_decode_row(&user_2, &input, row_rfx, &allocator);


  must("correctly decode the matching fields");
    verify(error.occurred == false);
    verify(streq("Esculapio", user_1.name.content));
    verify(user_1.age == 33);
    verify(streq("Romualdo", user_2.name.content));
    verify(user_2.age == 17);


  success();
    memory_release(&allocator);
}
