test( map_each, iterate_keys_and_values ) {

  given("a map");
    map<int, int> map = map_init(int, int, 16);
    map_set(&map, 7, 49);
    map_set(&map, 8, 64);
    map_set(&map, 9, 81);

    int index_tracer = 0;


  calling("map_each()");
  must("iterate over the keys and values of the map");
    for map_each(&map, int* key, int* value) {
      switch (iter.index) {
      case 0:
        verify(*key == 7);
        verify(*value == 49);
        break;

      case 1:
        verify(*key == 8);
        verify(*value == 64);
        break;

      case 2:
        verify(*key == 9);
        verify(*value == 81);
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
