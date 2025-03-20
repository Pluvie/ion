#include "http.h"

void test_suite__http (
    void
)
{
  test_add( http_parse_header, correct );
  test_add( http_parse_header, incorrect );
  test_add( http_parse_header, line_feed );
}
