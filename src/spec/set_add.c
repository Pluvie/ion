spec( set_add ) {

  argument(set<char*>* set);
  argument(char* element);

  when("the set is stack allocated") {
    #define stack_allocated_set_condition \
      set<char*> stack_set = set_init(char*, 8); \
      set = &stack_set;

    when("the set length is inferior to its load limit") {
      #define set_length_condition \
        set_add(set, "a"); \
        set_add(set, "b"); \
        set_add(set, "c");

      when("the element is present in the set") {
        element = "a";
        apply(stack_allocated_set_condition);
        apply(set_length_condition);
        int original_set_length = set->length;
        int original_set_capacity = set->capacity;
        int result = set_add(set, element);

        must("not fail");
          verify(unlikely(failure.occurred) == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("leave the set length unchanged");
          verify(set->length == original_set_length);

        must("leave the set capacity unchanged");
          verify(set->capacity == original_set_capacity);

        success();
      } end();

      when("the element is not present in the set") {
        element = "z";
        apply(stack_allocated_set_condition);
        apply(set_length_condition);
        int original_set_length = set->length;
        int original_set_capacity = set->capacity;
        int result = set_add(set, element);

        must("not fail");
          verify(unlikely(failure.occurred) == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("increase the set length by one");
          verify(set->length == original_set_length + 1);

        must("leave the set capacity unchanged");
          verify(set->capacity == original_set_capacity);

        success();
      } end();
    } end();
    #undef set_length_condition

    // when("the set is stack allocated")
    when("the set length is equal or greater than its load limit") {
      #define set_length_condition \
        set_add(set, "a"); \
        set_add(set, "b"); \
        set_add(set, "c"); \
        set_add(set, "d"); \
        set_add(set, "e"); \
        set_add(set, "f"); \
        set_add(set, "g"); \
        set_add(set, "h");

      when("the element is present in the set") {
        element = "a";
        apply(stack_allocated_set_condition);
        apply(set_length_condition);
        int original_set_length = set->length;
        int original_set_capacity = set->capacity;
        int result = set_add(set, element);

        must("not fail");
          verify(unlikely(failure.occurred) == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("leave the set length unchanged");
          verify(set->length == original_set_length);

        must("leave the set capacity unchanged");
          verify(set->capacity == original_set_capacity);

        success();
      } end();

      when("the element is not present in the set") {
        element = "z";
        apply(stack_allocated_set_condition);
        apply(set_length_condition);
        int original_set_length = set->length;
        int original_set_capacity = set->capacity;
        int result = set_add(set, element);

        must("fail with a specific error");
          verify(unlikely(failure.occurred) == true);
          verify(streq(failure.message, "add: stack allocated set is full"));

        must("return -1");
          verify(result == -1);

        must("leave the set length unchanged");
          verify(set->length == original_set_length);

        must("leave the set capacity unchanged");
          verify(set->capacity == original_set_capacity);

        success();
      } end();
    } end();
    #undef set_length_condition
  } end();
  #undef stack_allocated_set_condition

  when("the set is heap allocated") {
    #define heap_allocated_set_condition \
      set<char*>* set = set_alloc(char*, 16, spec_allocator); \
      set_add(set, "a"); \
      set_add(set, "b"); \
      set_add(set, "c");

    when("the set length is inferior to its load limit") {
      #define set_length_condition \
        set_add(set, "a"); \
        set_add(set, "b"); \
        set_add(set, "c");

      when("the element is present in the set") {
        element = "a";
        apply(heap_allocated_set_condition);
        apply(set_length_condition);
        int original_set_length = set->length;
        int original_set_capacity = set->capacity;
        int result = set_add(set, element);

        must("not fail");
          verify(unlikely(failure.occurred) == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("leave the set length unchanged");
          verify(set->length == original_set_length);

        must("leave the set capacity unchanged");
          verify(set->capacity == original_set_capacity);

        success();
      } end();

      when("the element is not present in the set") {
        element = "z";
        apply(heap_allocated_set_condition);
        apply(set_length_condition);
        int original_set_length = set->length;
        int original_set_capacity = set->capacity;
        int result = set_add(set, element);

        must("not fail");
          verify(unlikely(failure.occurred) == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("increase the set length by one");
          verify(set->length == original_set_length + 1);

        must("leave the set capacity unchanged");
          verify(set->capacity == original_set_capacity);

        success();
      } end();
    } end();
    #undef set_length_condition

    // when("the set is heap allocated")
    when("the set length is equal or greater than its load limit") {
      #define set_length_condition \
        char* elements[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k" }; \
        for (int i = 0; i < set->load_limit; i++) \
          set_add(set, elements[i]); \

      when("the element is present in the set") {
        element = "a";
        apply(heap_allocated_set_condition);
        apply(set_length_condition);
        int original_set_length = set->length;
        int original_set_capacity = set->capacity;
        int result = set_add(set, element);

        must("not fail");
          verify(unlikely(failure.occurred) == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("leave the set length unchanged");
          verify(set->length == original_set_length);

        must("increase the set capacity by a factor 2");
          verify(set->capacity == 2 * original_set_capacity);

        success();
      } end();

      when("the element is not present in the set") {
        element = "z";
        apply(heap_allocated_set_condition);
        apply(set_length_condition);
        int original_set_length = set->length;
        int original_set_capacity = set->capacity;
        int result = set_add(set, element);

        must("not fail");
          verify(unlikely(failure.occurred) == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("increase the set length by one");
          verify(set->length == original_set_length + 1);

        must("increase the set capacity by a factor 2");
          verify(set->capacity == 2 * original_set_capacity);

        success();
      } end();
    } end();
    #undef set_length_condition
  } end();
  #undef heap_allocated_set_condition
}
