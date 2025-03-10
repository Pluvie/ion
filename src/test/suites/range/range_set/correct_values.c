test( range_set, correct_values ) {

  given("a range");
    struct range range;


  when("providing a min and max values");
    i64 min = -3;
    i64 max = 7;


  calling("range_set()");
    range_set(&range, min, max);


  must("correctly set the range to the specified values");
    verify(range.min == min);
    verify(range.max == max);
    verify(range.at == min);


  success();
}
