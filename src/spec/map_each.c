spec( map_each ) {

  precondition("a valid map");
    #define preconditions \
      map<char*, int> map = map(char*, int, { { "a", 3 }, { "b", 4 }, { "c", 5 } });

  when("a custom index name is not given") {
    apply(preconditions);

    must("iterate over all entries of the map");
      int index = 0;
      for map_each(&map, char** key, int* value) {
        switch (index) {
        case 0:
          verify(streq(*key, "a"))
          verify(*value == 3);
          break;
        case 1:
          verify(streq(*key, "b"))
          verify(*value == 4);
          break;
        case 2:
          verify(streq(*key, "c"))
          verify(*value == 5);
          break;
        }
        index++;
      }

    success();
  } end();

  when("a custom index name is given") {
    apply(preconditions);

    must("iterate over all entries of the map using the provided index name");
      int index = 0;
      for map_each(&map, char** key, int* value, custom_index) {
        switch (index) {
        case 0:
          verify(streq(*key, "a"))
          verify(*value == 3);
          break;
        case 1:
          verify(streq(*key, "b"))
          verify(*value == 4);
          break;
        case 2:
          verify(streq(*key, "c"))
          verify(*value == 5);
        }

        verify(custom_index == index);
        index++;
      }

    success();
  } end();

  #undef preconditions
}
