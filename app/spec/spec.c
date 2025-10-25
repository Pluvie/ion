#include <ion.h>
#include <ion.c>

#define container_for   int
#define container_name  int_list
#include <ion/containers/list.h>
#define container_for   int
#define container_name  int_list
#include <ion/containers/list.c>

#define fmt_concat(type, format) type ## format
#define fmt(type) fmt_concat(type, _FORMAT)

int_t main (
    int_t argc,
    cstr* argv
)
{
  int data[] = { 7, 8, 9 };
  struct int_list l = { 0 };
  l.data = data;
  l.length = sizeof(data);

  printf("HELLO WORLD! number: {%"fmt(INT)"} [%"fmt(INT)"] --%"fmt(INT)"--\n", 42L, l.length, *int_list_at(&l, 1));
  return EXIT_SUCCESS;
}
