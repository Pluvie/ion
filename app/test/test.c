#include <ion.h>
#include <ion.c>

#define reflect(type, reflection_type) { \
  reflection_type, { 0 }, #type, sizeof(type) }
#define reflect_field(type, name, struct_type, reflection_type) { \
  reflection_type, { #name, sizeof(#name) - 1 }, #type, sizeof(type), offsetof(struct_type, name) }
#define reflect_nested(name, struct_type, reflection_type) { \
  reflection_type, { #name, sizeof(#name) - 1 }, nullptr, sizeof(((struct_type*) 0)->name), offsetof(struct_type, name) }
#define reflect_field_nested(type, name, struct_type, nested_name, reflection_type) { \
  reflection_type, { #name, sizeof(#name) - 1 }, #type, sizeof(type), offsetof(struct_type, nested_name.name) - offsetof(struct_type, nested_name) }


struct complex {
  int hey;
  int there;
  struct {
    int a;
    int b;
  } candoit;
  struct {
    int oh;
    int no;
  } why[3];
};

void reflection_example (
    void
)
{
  struct reflection rfx = reflect(struct complex, STRUCT);
  struct reflection candoit_rfx = reflect_nested(candoit, struct complex, STRUCT);
  struct reflection candoit_rfx_fields[] = {
    reflect_field_nested(int, a, struct complex, candoit, INT),
    reflect_field_nested(int, b, struct complex, candoit, INT),
    { 0 }
  };
  struct reflection why_rfx = reflect_nested(why, struct complex, ARRAY);
  struct reflection why_rfx_element = reflect_nested(why[0], struct complex, STRUCT);
  struct reflection why_rfx_element_fields[] = {
    reflect_field_nested(int, oh, struct complex, why[0], INT),
    reflect_field_nested(int, no, struct complex, why[0], INT),
    { 0 }
  };
  struct reflection rfx_fields[] = {
    reflect_field(int, hey, struct complex, INT),
    reflect_field(int, there, struct complex, INT),
    { 0 }, /* candoit_rfx */
    { 0 }, /* why_rfx */
    { 0 }
  };

  candoit_rfx.descendant = candoit_rfx_fields;
  why_rfx_element.descendant = why_rfx_element_fields;
  why_rfx.descendant = &why_rfx_element;

  rfx_fields[2] = candoit_rfx;
  rfx_fields[3] = why_rfx;
  rfx.descendant = rfx_fields;

  printf("reflection: { type: %"fmt(ENUM)", type_name: %"fmt(CSTR)", size: %"fmt(INT)" }\n", rfx.type, rfx.type_name, rfx.size);
  {
    struct reflection* field;
    for (field = rfx.descendant; field->type != 0; field++) {
      printf("field: {"
        " name: \"%"      fmt(STR)      "\","
        " type: %"        fmt(ENUM)     ","
        " type_name: \"%" fmt(CSTR)     "\","
        " size: %"        fmt(INT)      ","
        " offset: %"      fmt(UINT)     " "
        "}\n",
        str_fmt(field->name),
        field->type,
        field->type_name,
        field->size,
        field->offset);
    }
  }
  {
    struct reflection* field;
    for (field = candoit_rfx.descendant; field->type != 0; field++) {
      printf("candoit: {"
        " name: \"%"      fmt(STR)      "\","
        " type: %"        fmt(ENUM)     ","
        " type_name: \"%" fmt(CSTR)     "\","
        " size: %"        fmt(INT)      ","
        " offset: %"      fmt(UINT)     " "
        "}\n",
        str_fmt(field->name),
        field->type,
        field->type_name,
        field->size,
        field->offset);
    }
  }
  {
    struct reflection* field;
    printf("why_element: {"
      " name: \"%"      fmt(STR)      "\","
      " type: %"        fmt(ENUM)     ","
      " type_name: \"%" fmt(CSTR)     "\","
      " size: %"        fmt(INT)      ","
      " offset: %"      fmt(UINT)     " "
      "}\n",
      str_fmt(why_rfx_element.name),
      why_rfx_element.type,
      why_rfx_element.type_name,
      why_rfx_element.size,
      why_rfx_element.offset);
    for (field = why_rfx_element.descendant; field->type != 0; field++) {
      printf("why: {"
        " name: \"%"      fmt(STR)      "\","
        " type: %"        fmt(ENUM)     ","
        " type_name: \"%" fmt(CSTR)     "\","
        " size: %"        fmt(INT)      ","
        " offset: %"      fmt(UINT)     " "
        "}\n",
        str_fmt(field->name),
        field->type,
        field->type_name,
        field->size,
        field->offset);
    }
  }
}

#define container_for   int
#define container_name  int_list
#include <ion/containers/list.h>
#define container_for   int
#define container_name  int_list
#include <ion/containers/list.c>

#define container_for   int
#define container_name  int_set
#include <ion/containers/set.h>
#define container_for   int
#define container_name  int_set
#define container_equalizer(a, b) a == b
#define container_hasher(e) e
#include <ion/containers/set.c>

#define container_for_key   int
#define container_for_value int
#define container_name  int_map
#include <ion/containers/map.h>
#define container_for_key   int
#define container_for_value int
#define container_name  int_map
#define container_equalizer(a, b) a == b
#define container_hasher(e) e
#include <ion/containers/map.c>

void data_example (
    void
)
{
  int data[] = { 7, 8, 9 };
  struct int_list l = { 0 };
  struct allocator allocator = allocator_init(0);
  struct int_set s = int_set_alloc(0, &allocator);
  struct int_map m = int_map_alloc(0, &allocator);

  l.data = data;
  l.length = sizeof(data);
  printf("HELLO WORLD! number: {%"fmt(INT)"} [%"fmt(INT)"] --%"fmt(INT)"--\n", 42L, l.length, *int_list_at(&l, 1));

  int_set_add(&s, 7);
  int_set_add(&s, 8);
  int_set_add(&s, 9);
  printf("set { length: %"fmt(UINT)" }\n", s.length);
  printf("7? %"fmt(CSTR)"\n", int_set_has(&s, 7) ? "true" : "false");
  printf("8? %"fmt(CSTR)"\n", int_set_has(&s, 8) ? "true" : "false");
  printf("9? %"fmt(CSTR)"\n", int_set_has(&s, 9) ? "true" : "false");
  printf("5? %"fmt(CSTR)"\n", int_set_has(&s, 5) ? "true" : "false");

  int_map_set(&m, 7, 10);
  int_map_set(&m, 8, 11);
  int_map_set(&m, 9, 12);
  printf("map { length: %"fmt(UINT)" }\n", m.length);
  printf("7: %"fmt(INT)"\n", *int_map_get(&m, 7));
  printf("8: %"fmt(INT)"\n", *int_map_get(&m, 8));
  printf("9: %"fmt(INT)"\n", *int_map_get(&m, 9));

  allocator_release(&allocator);
}

int_t main (
    int_t argc,
    cstr* argv
)
{
  data_example();
  reflection_example();

  return EXIT_SUCCESS;
}
