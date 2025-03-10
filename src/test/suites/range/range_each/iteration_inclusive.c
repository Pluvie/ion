test( range_each, iteration_inclusive ) {

  given("a range");
    struct range range = { -5, 5 };

  calling("range_each()");
    i64 range_numbers[11] = { 0 };
    for range_each(range, index)
      range_numbers[index] = range.at;


  must("correctly iterate the range values inclusively");
    for (i64 i = 0; i < lengthof(range_numbers); i++)
      switch (i) {
      case 0:
        verify(range_numbers[i] == -5);
        continue;
      case 1:
        verify(range_numbers[i] == -4);
        continue;
      case 2:
        verify(range_numbers[i] == -3);
        continue;
      case 3:
        verify(range_numbers[i] == -2);
        continue;
      case 4:
        verify(range_numbers[i] == -1);
        continue;
      case 5:
        verify(range_numbers[i] == 0);
        continue;
      case 6:
        verify(range_numbers[i] == 1);
        continue;
      case 7:
        verify(range_numbers[i] == 2);
        continue;
      case 8:
        verify(range_numbers[i] == 3);
        continue;
      case 9:
        verify(range_numbers[i] == 4);
        continue;
      case 10:
        verify(range_numbers[i] == 5);
        continue;
      }


  success();
}
