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

int_t main (
    int_t argc,
    cstr* argv
)
{
  int data[] = { 7, 8, 9 };
  struct int_list l = { 0 };
  struct reflection rfx = reflect(struct complex, STRUCT);
  struct reflection candoit_rfx = reflect_nested(candoit, struct complex, STRUCT);
  struct reflection candoit_rfx_fields[] = {
    reflect_field_nested(int, a, struct complex, candoit, INT),
    reflect_field_nested(int, b, struct complex, candoit, INT),
    { 0 }
  };
  struct reflection why_rfx = reflect_nested(why, struct complex, ARRAY);
  struct reflection why_rfx_element[] = {
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

  candoit_rfx.children = candoit_rfx_fields;
  why_rfx.children = why_rfx_element;

  rfx_fields[2] = candoit_rfx;
  rfx_fields[3] = why_rfx;
  rfx.children = rfx_fields;

  l.data = data;
  l.length = sizeof(data);

  printf("HELLO WORLD! number: {%"fmt(INT)"} [%"fmt(INT)"] --%"fmt(INT)"--\n", 42L, l.length, *int_list_at(&l, 1));

  printf("reflection: { type: %"fmt(ENUM)", type_name: %"fmt(CSTR)", size: %"fmt(INT)" }\n", rfx.type, rfx.type_name, rfx.size);
  {
    struct reflection* field;
    for (field = rfx.children; field->type != 0; field++) {
      printf("reflection: {"
        " name: %"      fmt(STR)      ","
        " type: %"      fmt(UINT_T)   ","
        " type_name: %" fmt(CSTR)     ","
        " size: %"      fmt(INT)      ","
        " offset: %"    fmt(UINT)     " "
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
    for (field = candoit_rfx.children; field->type != 0; field++) {
      printf("candoit: {"
        " name: %"      fmt(STR)      ","
        " type: %"      fmt(UINT_T)   ","
        " type_name: %" fmt(CSTR)     ","
        " size: %"      fmt(INT)      ","
        " offset: %"    fmt(UINT)     " "
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
    for (field = why_rfx.children; field->type != 0; field++) {
      printf("why: {"
        " name: %"      fmt(STR)      ","
        " type: %"      fmt(UINT_T)   ","
        " type_name: %" fmt(CSTR)     ","
        " size: %"      fmt(INT)      ","
        " offset: %"    fmt(UINT)     " "
        "}\n",
        str_fmt(field->name),
        field->type,
        field->type_name,
        field->size,
        field->offset);
    }
  }

  return EXIT_SUCCESS;
}
