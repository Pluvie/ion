spec( set_has ) {

  argument(set<char*>* set);
  argument(char* key);

  when("the set is stack allocated") {
    #define stack_allocated_set_condition \
      set<char*> stack_set = set_init(char*, 16); \
      set = &stack_set; \
      set_add(set, "a"); \
      set_add(set, "b"); \
      set_add(set, "c");

    when("the key is present in the set") {
      key = "a";
      apply(stack_allocated_set_condition);
      bool result = set_has(set, key);

      must("not fail");
        verify(error.occurred == false);

      must("return true");
        verify(result == true);

      success();
    }

    or_when("the key is not present in the set") {
      key = "f";
      apply(stack_allocated_set_condition);
      bool result = set_has(set, key);

      must("not fail");
        verify(error.occurred == false);

      must("return false");
        verify(result == false);

      success();
    }
  }
  #undef stack_allocated_set_condition

  or_when("the set is heap allocated") {
    #define heap_allocated_set_condition \
      set<char*>* set = set_alloc(char*, 16, spec_allocator); \
      set_add(set, "a"); \
      set_add(set, "b"); \
      set_add(set, "c");

    when("the key is present in the set") {
      key = "a";
      apply(heap_allocated_set_condition);
      bool result = set_has(set, key);

      must("not fail");
        verify(error.occurred == false);

      must("return true");
        verify(result == true);

      success();
    }

    or_when("the key is not present in the set") {
      key = "f";
      apply(heap_allocated_set_condition);
      bool result = set_has(set, key);

      must("not fail");
        verify(error.occurred == false);

      must("return false");
        verify(result == false);

      success();
    }
  }
  #undef heap_allocated_set_condition
}
