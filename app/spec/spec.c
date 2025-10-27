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
    /*reflect_field(int, candoit.a, struct complex, INT),
    reflect_field(int, candoit.b, struct complex, INT),
    reflect_field(((struct complex*) 0)->why, why, struct complex, ARRAY),*/
    { 0 }
  };

  candoit_rfx.linked.fields = candoit_rfx_fields;
  why_rfx_element.linked.fields = why_rfx_element_fields;
  why_rfx.linked.element = &why_rfx_element;

  rfx_fields[2] = candoit_rfx;
  rfx_fields[3] = why_rfx;
  rfx.linked.fields = rfx_fields;

  printf("reflection: { type: %"fmt(ENUM)", type_name: %"fmt(CSTR)", size: %"fmt(INT)" }\n", rfx.type, rfx.type_name, rfx.size);
  {
    struct reflection* field;
    for (field = rfx.linked.fields; field->type != 0; field++) {
      printf("field: {"
        " name: \"%"      fmt(STR)      "\","
        " type: %"        fmt(UINT_T)   ","
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
    for (field = candoit_rfx.linked.fields; field->type != 0; field++) {
      printf("candoit: {"
        " name: \"%"      fmt(STR)      "\","
        " type: %"        fmt(UINT_T)   ","
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
      " type: %"        fmt(UINT_T)   ","
      " type_name: \"%" fmt(CSTR)     "\","
      " size: %"        fmt(INT)      ","
      " offset: %"      fmt(UINT)     " "
      "}\n",
      str_fmt(why_rfx_element.name),
      why_rfx_element.type,
      why_rfx_element.type_name,
      why_rfx_element.size,
      why_rfx_element.offset);
    for (field = why_rfx_element.linked.fields; field->type != 0; field++) {
      printf("why: {"
        " name: \"%"      fmt(STR)      "\","
        " type: %"        fmt(UINT_T)   ","
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

void set_example (
    void
)
{
  int data[] = { 7, 8, 9 };
  struct int_list l = { 0 };
  struct int_set s = { 0 };

  l.data = data;
  l.length = sizeof(data);
  printf("HELLO WORLD! number: {%"fmt(INT)"} [%"fmt(INT)"] --%"fmt(INT)"--\n", 42L, l.length, *int_list_at(&l, 1));

  int_set_add(&s, 7);
  int_set_add(&s, 8);
  int_set_add(&s, 9);
  printf("set { length: %"fmt(UINT)" }\n", s.length);
}

int_t main (
    int_t argc,
    cstr* argv
)
{
  set_example();
  reflection_example();

  return EXIT_SUCCESS;
}
