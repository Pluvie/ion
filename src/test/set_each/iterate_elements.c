test( set_each, iterate_elements ) {

  given("a set");
    set<int> set = set_init(int, 16);
    set_add(&set, 7);
    set_add(&set, 8);
    set_add(&set, 9);

    int index_tracer = 0;


  calling("set_each()");
  must("iterate over the elements of the set");
    for set_each(&set, int* element, optional_index) {
      switch (optional_index) {
      case 0:
        verify(*element == 7);
        break;

      case 1:
        verify(*element == 8);
        break;

      case 2:
        verify(*element == 9);
        break;

      default:
        /* NOTE(Pluvie): this code point should not be reached ever, hence the
         * `verify(false)` guard. */
        verify(false);
      }
      index_tracer++;
    }
    verify(index_tracer == 3);


  success();
}
