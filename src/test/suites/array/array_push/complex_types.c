test( array_push, complex_types ) {

  given("a declined array on a complex user defined type");
    array(User) array = array_init(User)(0, test_allocator);


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


  calling("array_push()");
    array_push(User)(&array, &gerry);
    array_push(User)(&array, &albert);
    array_push(User)(&array, &esculapio);


  must("store the correct values of this type");
    User* user;

    user = array_get(User)(&array, 0);
    verify(streq(user->name, s("Gerry")));
    verify(user->age == 37);

    user = array_get(User)(&array, 1);
    verify(streq(user->name, s("Albert")));
    verify(user->age == 25);

    user = array_get(User)(&array, 2);
    verify(streq(user->name, s("Esculapio")));
    verify(user->age == 99);


  success();
}
