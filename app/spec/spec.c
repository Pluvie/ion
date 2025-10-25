#include <ion.h>
#include <ion.c>

#define container_for   int
#define container_name  int_list
#include <ion/containers/list.h>
#define container_for   int
#define container_name  int_list
#include <ion/containers/list.c>

#define reflect(type, reflection_type) { \
  reflection_type, { 0 }, #type, sizeof(type) }

struct reflection rfx = reflect(int, INT);

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
  printf("reflection: { type: %"fmt(UINT_T)", type_name: %"fmt(CSTR)", size: %"fmt(INT)" }\n", rfx.type, rfx.type_name, rfx.size);
  return EXIT_SUCCESS;
}
