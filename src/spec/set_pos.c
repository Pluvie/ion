spec( set_pos ) {

  argument(set<char*>* set);
  argument(char* element);

  precondition("a valid set");
    #define preconditions \
      set<char*> valid_set = set_init(char*, 16); \
      set = &valid_set; \
      set_add(set, "a"); \
      set_add(set, "b"); \
      set_add(set, "c"); \
      set_add(set, "d"); \
      set_add(set, "e"); \
      set_add(set, "f"); \
      set_add(set, "g");

  when("the element is present in the set") {
    apply(preconditions);
    int result;
    char* elements[] = { "a", "b", "c", "d", "e", "f", "g" };
    int positions[] = { 6, 7, 8, 9, 10, 11, 12 };

    must("not fail");
    must("return the correct element position");
    for (int i = 0; i < countof(elements); i++) {
      element = elements[i];
      result = set_pos(set, element);
      verify(error.occurred == false);
      verify(result == positions[i]);
    }
    success();
  }

  or_when("the element is not present in the set") {
    element = "z";

    when("the set has free positions") {
      apply(preconditions);

      int result = set_pos(set, element);

      must("not fail");
        verify(error.occurred == false);

      must("return a valid free position");
        verify(result >= 0);

      success();
    }

    or_when("the set is full") {
      apply(preconditions);
      set_add(set, "h");
      set_add(set, "i");
      set_add(set, "j");
      set_add(set, "k");
      set_add(set, "l");
      set_add(set, "m");
      set_add(set, "n");
      set_add(set, "o");
      set_add(set, "p");

      int result = set_pos(set, element);

      must("not fail");
        verify(error.occurred == false);

      must("return -1");
        verify(result == -1);

      success();
    }
  }

  #undef preconditions
}
