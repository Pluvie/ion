#include "time.h"

void test_suite__time (
    void
)
{
  test_add( date, day_month_year );
  test_add( date_to_string, format );
  test_add( date_today, correct_number );
  test_add( time_now, correct_number );
  test_add( time_to_string, format );
}
