test( array_each, iterate_elements ) {

  given("a declined array");
    array(string) array = array_init(string)(0, test_allocator);


  when("the array has some keys in it");
    array_push(string)(&array, &s("Mercury"));
    array_push(string)(&array, &s("Venus"));
    array_push(string)(&array, &s("Earth"));
    array_push(string)(&array, &s("Mars"));
    array_push(string)(&array, &s("Jupiter"));
    array_push(string)(&array, &s("Saturn"));
    array_push(string)(&array, &s("Uranus"));
    array_push(string)(&array, &s("Neptune"));
    array_push(string)(&array, &s("Pluto"));


  calling("array_each()");
  must("loop over the keys and values of the array");
    array_iterator(string) iter = { 0 };
    for array_each(&array, iter)
      switch (iter.index) {
      case 0:
        verify(streq(*iter.value, s("Mercury")));
        break;
      case 1:
        verify(streq(*iter.value, s("Venus")));
        break;
      case 2:
        verify(streq(*iter.value, s("Earth")));
        break;
      case 3:
        verify(streq(*iter.value, s("Mars")));
        break;
      case 4:
        verify(streq(*iter.value, s("Jupiter")));
        break;
      case 5:
        verify(streq(*iter.value, s("Saturn")));
        break;
      case 6:
        verify(streq(*iter.value, s("Uranus")));
        break;
      case 7:
        verify(streq(*iter.value, s("Neptune")));
        break;
      case 8:
        verify(streq(*iter.value, s("Pluto")));
        break;
      }
    verify(iter.index == 9);


  success();
    memory_release(test_allocator);
}
