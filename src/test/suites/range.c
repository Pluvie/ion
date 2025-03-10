#include "range.h"

void test_suite__range (
    void
)
{
  test_add( range_set, correct_values );
  test_add( range_each, iteration_inclusive );
}
