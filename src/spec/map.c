spec( map ) {

  precondition("a valid key type");
  precondition("a valid value type");
    #define valid_key_type    char*
    #define valid_value_type  struct squadmate

  precondition("a valid list of key/value pairs of those types")
    #define valid_key_value_pairs { \
      { "Jane Shepard",     { .class = SOLDIER,     .health = 800, .shields = 400 } }, \
      { "Garrus Vakarian",  { .class = INFILTRATOR, .health = 600, .shields = 600 } }, \
      { "Liara T'Soni",     { .class = ADEPT,       .health = 200, .shields = 800 } }, \
    }

  must("create a frozen stack allocated map of the given key/value pairs");
    void* stack_begin = &(int) { 0 };
    void *stack_end = __builtin_frame_address(0);

    map<char*, struct squadmate> squad = map(
      valid_key_type, valid_value_type, valid_key_value_pairs);

    verify((void*) squad.keys.data >= stack_begin);
    verify((void*) squad.keys.data <= stack_end);
    verify((void*) squad.values >= stack_begin);
    verify((void*) squad.values <= stack_end);
    verify(squad.keys.allocator == NULL);
    verify(squad.keys.capacity == 3);
    verify(squad.keys.length == 3);
    verify(squad.length == 3);

  success();

  #undef valid_key_type
  #undef valid_value_type
  #undef valid_key_value_pairs
}
