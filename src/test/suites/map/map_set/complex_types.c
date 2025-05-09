test( map_set, complex_types ) {

  given("a declined map on a complex user defined type");
    map(string, User) map = map_init(string, User)(0, test_allocator);


  given("some values of this type");
    User gerry = {
      .name = s("Gerry"),
      .age = 37,
    };

    User albert = {
      .name = s("Albert"),
      .age = 25,
    };

    User esculapio = {
      .name = s("Esculapio"),
      .age = 99,
    };


  calling("map_set()");
    map_set(string, User)(&map, &gerry.name, &gerry);
    map_set(string, User)(&map, &albert.name, &albert);
    map_set(string, User)(&map, &esculapio.name, &esculapio);


  must("store the correct values of this type");
    User* user;

    user = map_get(string, User)(&map, &s("Gerry"));
    verify(streq(user->name, s("Gerry")));
    verify(user->age == 37);

    user = map_get(string, User)(&map, &s("Albert"));
    verify(streq(user->name, s("Albert")));
    verify(user->age == 25);

    user = map_get(string, User)(&map, &s("Esculapio"));
    verify(streq(user->name, s("Esculapio")));
    verify(user->age == 99);


  success();
}
