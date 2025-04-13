test( map_set, complex_types ) {

  given("a declined map on a complex user defined type");
    memory allocator = memory_init(0);
    map(string, type(user)) m = map_init(string, type(user))(0, &allocator);


  when("there are values for those types");
    type(user) gerry = {
      .name = s("Gerry"),
      .age = 37,
    };

    type(user) albert = {
      .name = s("Albert"),
      .age = 25,
    };

    type(user) esculapio = {
      .name = s("Esculapio"),
      .age = 99,
    };


  calling("map_set()");
    map_set(string, type(user))(&m, &(gerry.name), &gerry);
    map_set(string, type(user))(&m, &(albert.name), &albert);
    map_set(string, type(user))(&m, &(esculapio.name), &esculapio);


  must("store the correct values of their type");
    type(user)* user;

    user = map_get(string, type(user))(&m, &s("Gerry"));
    verify(streq(user->name, s("Gerry")));
    verify(user->age == 37);

    user = map_get(string, type(user))(&m, &s("Albert"));
    verify(streq(user->name, s("Albert")));
    verify(user->age == 25);

    user = map_get(string, type(user))(&m, &s("Esculapio"));
    verify(streq(user->name, s("Esculapio")));
    verify(user->age == 99);


  success();
    memory_release(&allocator);
}
