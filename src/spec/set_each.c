spec( set_each ) {

  precondition("a valid set");
    #define preconditions \
      set<char*> set = set(char*, { "a", "b", "c" });

  when("a custom index name is not given") {
    apply(preconditions);

    must("iterate over all entries of the set");
      int index = 0;
      for set_each(&set, char** element) {
        switch (index) {
        case 0:
          verify(streq(*element, "a"))
          break;
        case 1:
          verify(streq(*element, "b"))
          break;
        case 2:
          verify(streq(*element, "c"))
          break;
        }
        index++;
      }

    success();
  } end();

  when("a custom index name is given") {
    apply(preconditions);

    must("iterate over all entries of the set using the provided index name");
      int index = 0;
      for set_each(&set, char** element, custom_index) {
        switch (index) {
        case 0:
          verify(streq(*element, "a"))
          break;
        case 1:
          verify(streq(*element, "b"))
          break;
        case 2:
          verify(streq(*element, "c"))
        }

        verify(custom_index == index);
        index++;
      }

    success();
  } end();

  #undef preconditions
}
