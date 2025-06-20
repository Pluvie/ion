test( map, user_defined_types ) {

  given("the Mass Effect squadmates pool");
    map<string, struct squadmate> squadmates = map(string, struct squadmate, {
      { s("Kaidan Alenko"),       { s("Kaidan Alenko"), SENTINEL, 300, 400 } },
      { s("Ashley Williams"),     { s("Ashley Williams"), SOLDIER, 400, 700 } },
      { s("Garrus Vakarian"),     { s("Garrus Vakarian"), INFILTRATOR, 300, 500 } },
      { s("Tali Zorah"),          { s("Tali Zorah"), ENGINEER, 200, 400 } },
      { s("Urdnot Wrex"),         { s("Urdnot Wrex"), VANGUARD, 800, 800 } },
      { s("Liara T'Soni"),        { s("Liara T'Soni"), ADEPT, 100, 600 } },
    });


  given("a selectable shore party");
    struct squadmate shore_party[2] = { 0 };


  when("selecting a biotic heavy squad");
    shore_party[0] = *map_get(&squadmates, s("Liara T'Soni"));
    shore_party[1] = *map_get(&squadmates, s("Urdnot Wrex"));
    verify(shore_party[0].class == ADEPT);
    verify(shore_party[1].class == VANGUARD);


  when("selecting a biotic light squad");
    shore_party[0] = *map_get(&squadmates, s("Liara T'Soni"));
    shore_party[1] = *map_get(&squadmates, s("Kaidan Alenko"));
    verify(shore_party[0].class == ADEPT);
    verify(shore_party[1].class == SENTINEL);


  when("selecting a combat heavy squad");
    shore_party[0] = *map_get(&squadmates, s("Ashley Williams"));
    shore_party[1] = *map_get(&squadmates, s("Urdnot Wrex"));
    verify(shore_party[0].class == SOLDIER);
    verify(shore_party[1].class == VANGUARD);


  when("selecting a combat light squad");
    shore_party[0] = *map_get(&squadmates, s("Ashley Williams"));
    shore_party[1] = *map_get(&squadmates, s("Garrus Vakarian"));
    verify(shore_party[0].class == SOLDIER);
    verify(shore_party[1].class == INFILTRATOR);


  when("selecting a tech combat squad");
    shore_party[0] = *map_get(&squadmates, s("Tali Zorah"));
    shore_party[1] = *map_get(&squadmates, s("Garrus Vakarian"));
    verify(shore_party[0].class == ENGINEER);
    verify(shore_party[1].class == INFILTRATOR);


  when("selecting a tech biotic squad");
    shore_party[0] = *map_get(&squadmates, s("Tali Zorah"));
    shore_party[1] = *map_get(&squadmates, s("Kaidan Alenko"));
    verify(shore_party[0].class == ENGINEER);
    verify(shore_party[1].class == SENTINEL);


  success();
}
