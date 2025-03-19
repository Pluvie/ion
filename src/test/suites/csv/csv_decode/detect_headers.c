test( csv_decode, detect_headers ) {

  given("a csv file");
    char* csv_file =
      "USERNAME,AGE,LAST_LOGIN\n"
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
    verify(user->last_login.content == NULL);

    user = array_get(&users, 1);
    verify(streq("Romualdo", user->name.content));
    verify(user->age == 17);
    verify(user->last_login.content == NULL);


  success();
    memory_release(&allocator);
}
