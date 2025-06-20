test( list_each, iterate_elements ) {

  given("a list");
    list<int> list = list_init(int, 16);
    list_push(&list, 7);
    list_push(&list, 8);
    list_push(&list, 9);

    int index_tracer = 0;


  calling("list_each()");
  must("iterate over the elements of the list");
    for list_each(&list, int* element, optional_index) {
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
