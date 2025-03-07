#include "date.h"

void test_suite__date (
    void
)
{
  test_add( date, day_month_year );
  test_add( date_to_string, format );
  test_add( date_today, correct_number );
}
