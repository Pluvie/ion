test( map_set, complex_types ) {

  given("a struct map");
    struct map map;
    struct memory allocator = memory_init(0);


  when("the map has key and values of complex types");
    struct user {
      char name[32];
      u64 age;
      struct vector* roles;
    };

    map = map_init(sizeof(char[32]), sizeof(struct user), 0, &allocator);


  when("there are values for those types");
    char names[][32] = { "Gerry", "Albert", "Esculapio" };
    enum roles {
      BOSS,
      ADMIN,
      EDITOR,
      VIEWER,
    };

    struct user gerry = {
      .name = "Gerry",
      .age = 37,
      .roles = &vector_of(enum roles, { ADMIN, EDITOR }),
    };

    struct user albert = {
      .name = "Albert",
      .age = 25,
      .roles = &vector_of(enum roles, { VIEWER }),
    };

    struct user esculapio = {
      .name = "Esculapio",
      .age = 99,
      .roles = &vector_of(enum roles, { BOSS }),
    };


  calling("map_set()");
    map_set(&map, names[0], &gerry);
    map_set(&map, names[1], &albert);
    map_set(&map, names[2], &esculapio);


  must("store the correct values of their type");
    struct user* user;

    user = map_get(&map, (char[32]) { "Gerry" });
    verify(streq("Gerry", user->name));
    verify(user->age == 37);
    verify(ADMIN == as(enum roles, vector_get(user->roles, 0)));
    verify(EDITOR == as(enum roles, vector_get(user->roles, 1)));

    user = map_get(&map, (char[32]) { "Albert" });
    verify(streq("Albert", user->name));
    verify(user->age == 25);
    verify(VIEWER == as(enum roles, vector_get(user->roles, 0)));

    user = map_get(&map, (char[32]) { "Esculapio" });
    verify(streq("Esculapio", user->name));
    verify(user->age == 99);
    verify(BOSS == as(enum roles, vector_get(user->roles, 0)));


  success();
    memory_release(&allocator);
}
