test( array_push, increase_length ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);
    array = array_init(sizeof(u64), 8, &allocator);
    verify(array.length == 0);


  calling("array_push()");
    array_push(&array, &(u64) { 2 });


  must("increase the array length");
    u64 element = as(u64, array_get(&array, 0));
    verify(element == 2);
    verify(array.length == 1);


  success();
    memory_release(&allocator);
}
