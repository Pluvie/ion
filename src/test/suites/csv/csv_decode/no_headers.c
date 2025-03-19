test( csv_decode, no_headers ) {

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
          { field(last_login, STRING, struct user), named("LAST_LOGIN") },
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
    rfx.support_data = &csv;


  calling("csv_decode()");
    struct memory allocator = memory_init(0);
    struct io input = io_open_memory(csv_file, strlen(csv_file));
    csv_decode(&users, &input, &rfx, &allocator);


  must("correctly decode the matching fields by detecting the headers");
    verify(error.occurred == false);

    struct user* user;

    user = array_get(&users, 0);
    verify(streq("Esculapio", user->name.content));
    verify(user->age == 33);
    verify(streq("1-jan-99", user->last_login.content));

    user = array_get(&users, 1);
    verify(streq("Romualdo", user->name.content));
    verify(user->age == 17);
    verify(streq("31-dec-99", user->last_login.content));


  success();
    memory_release(&allocator);
}
