#include "reflection.h"

spec( reflection ) {

  when("reflecting an array type") {
    when("the array type is reflected by its type") {
      int cube[3][3][3];
      struct reflection rfx = reflect(int[3][3][3], ARRAY,
        of(reflect(int, INT))
      );

      must("correctly define the reflection");
        verify(rfx.type == ARRAY);
        verify(str_empty(rfx.name));
        verify(cstr_equal(rfx.type_name, "long int[3][3][3]"));
        verify(rfx.size == sizeof(cube));

        verify(rfx.element != nullptr);
        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == INT);
        verify(str_empty(element_rfx->name));
        verify(cstr_equal(element_rfx->type_name, "long int"));
        verify(element_rfx->size == sizeof(int));

      success();
    } end();

    when("the array type is reflected by a variable name") {
      struct chess_square {
        bool is_occupied;
        str piece;
      };
      struct chess_square chess_board[8][8];

      /*
        Here we reflect the array by using the name of the `chess_board` variable.
      */
      struct reflection rfx = reflect(chess_board, ARRAY, of(
        reflect(struct chess_square, STRUCT, fields(
          field(struct chess_square, BOOL, is_occupied),
          field(struct chess_square, STR, piece),
        ))
      ));

      must("correctly define the reflection");
        verify(rfx.type == ARRAY);
        verify(str_empty(rfx.name));
        verify(cstr_equal(rfx.type_name, "chess_board"));
        verify(rfx.size == sizeof(chess_board));

        verify(rfx.element != nullptr);
        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == STRUCT);
        verify(str_empty(element_rfx->name));
        verify(cstr_equal(element_rfx->type_name, "struct chess_square"));
        verify(element_rfx->size == sizeof(struct chess_square));

        verify(element_rfx->fields != nullptr);
        struct reflection* field_rfx;
        field_rfx = element_rfx->fields + 0;
        verify(field_rfx->type == BOOL);
        verify(str_equal(field_rfx->name, string("is_occupied")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(bool));
        verify(field_rfx->offset == offsetof(struct chess_square, is_occupied));

        field_rfx = element_rfx->fields + 1;
        verify(field_rfx->type == STR);
        verify(str_equal(field_rfx->name, string("piece")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(str));
        verify(field_rfx->offset == offsetof(struct chess_square, piece));

      success();
    } end();

    #if standard(>= C23)
    when("the array type is reflected by inference") {
      struct example {
        int value_int;
        struct {
          int value_int;
          dec value_dec;
        } why[3];
      };

      /*
        Since the array is a tagless struct, and it is not associated to any
        variable, we must use the typeof macro -- available since C23 -- to get its
        type, along with the `o` macro to get a reference to the `struct { .. } why`
        field inside the `struct example`.
      */
      struct reflection rfx = reflect(struct example, STRUCT, fields(
        field(struct example, INT, value_int),
        field(struct example, ARRAY, why, of(
          reflect(typeof(o(struct example)->why), STRUCT, fields(
            field(typeof(*o(struct example)->why), INT, value_int),
            field(typeof(*o(struct example)->why), DEC, value_dec),
          )))
        ),
      ));

      must("correctly define the reflection");
        verify(rfx.type == STRUCT);
        verify(str_empty(rfx.name));
        verify(cstr_equal(rfx.type_name, "struct example"));
        verify(rfx.size == sizeof(struct example));

        verify(rfx.fields != nullptr);
        struct reflection* field_rfx;
        field_rfx = rfx.fields + 0;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("value_int")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct example, value_int));

        field_rfx = rfx.fields + 1;
        verify(field_rfx->type == ARRAY);
        verify(str_equal(field_rfx->name, string("why")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(o(struct example)->why));
        verify(field_rfx->offset == offsetof(struct example, why));
        verify(field_rfx->element != nullptr);

        struct reflection* element_rfx;
        element_rfx = field_rfx->element;
        verify(element_rfx->type == STRUCT);
        verify(str_empty(element_rfx->name));
        verify(cstr_equal(element_rfx->type_name, "typeof(((struct example*) 0)->why)"));
        verify(element_rfx->size == sizeof(o(struct example)->why));

        verify(element_rfx->fields != nullptr);
        field_rfx = element_rfx->fields + 0;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("value_int")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(typeof(*o(struct example)->why), value_int));

        field_rfx = element_rfx->fields + 1;
        verify(field_rfx->type == DEC);
        verify(str_equal(field_rfx->name, string("value_dec")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(dec));
        verify(field_rfx->offset == offsetof(typeof(*o(struct example)->why), value_dec));

      success();
    } end();
    #endif
  } end();

  when("reflecting a struct type") {
    when("the struct type is reflected by its type") {
      struct example {
        int value_int;
        dec value_dec;
      };

      struct reflection rfx = reflect(struct example, STRUCT, fields(
        field(struct example, INT, value_int),
        field(struct example, DEC, value_dec),
      ));

      must("correctly define the reflection");
        verify(rfx.type == STRUCT);
        verify(str_empty(rfx.name));
        verify(cstr_equal(rfx.type_name, "struct example"));
        verify(rfx.size == sizeof(struct example));

        verify(rfx.fields != nullptr);
        struct reflection* field_rfx;
        field_rfx = rfx.fields + 0;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("value_int")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct example, value_int));

        field_rfx = rfx.fields + 1;
        verify(field_rfx->type == DEC);
        verify(str_equal(field_rfx->name, string("value_dec")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(dec));
        verify(field_rfx->offset == offsetof(struct example, value_dec));

      success();
    } end();

    when("the struct type is reflected using a #define directive") {
      struct example {
        int value_int;
        dec value_dec;
        struct {
          int* number_ptr;
          int number;
          struct {
            int* number_ptr;
            int number;
          } inside_2;
        } inside_1;
      };

      /*
        We can define the struct type to a constant to avoid repeated typing.
        Just remember to undefine it when done!

        Also note how the `inside_2` struct is reflected by using a `inside_1.inside_2`
        path on the `field` macro: this is to reference correctly the `inside_2`
        field offsets without having to gather the struct type. This can be done only
        on nested structs.
      */
      #define t struct example
      struct reflection rfx = reflect(t, STRUCT, fields(
        field(t, INT,     value_int),
        field(t, DEC,     value_dec),
        field(t, STRUCT,  inside_1, fields(
          field_nested(t, POINTER, number_ptr, inside_1, of(reflect(int, INT))),
          field_nested(t, INT,     number,     inside_1),
          field_nested(t, STRUCT,  inside_2,   inside_1, fields(
            field_nested(t, POINTER, number_ptr, inside_1.inside_2, of(reflect(int, INT))),
            field_nested(t, INT,     number,     inside_1.inside_2),
          )),
        )),
      ));
      #undef t

      must("correctly define the reflection");
        verify(rfx.type == STRUCT);
        verify(str_empty(rfx.name));
        verify(cstr_equal(rfx.type_name, "struct example"));
        verify(rfx.size == sizeof(struct example));

        verify(rfx.fields != nullptr);
        struct reflection* field_rfx;
        field_rfx = rfx.fields + 0;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("value_int")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct example, value_int));

        field_rfx = rfx.fields + 1;
        verify(field_rfx->type == DEC);
        verify(str_equal(field_rfx->name, string("value_dec")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(dec));
        verify(field_rfx->offset == offsetof(struct example, value_dec));

        struct example example;
        struct reflection* inside_1_rfx = rfx.fields + 2;
        verify(inside_1_rfx->type == STRUCT);
        verify(str_equal(inside_1_rfx->name, string("inside_1")));
        verify(inside_1_rfx->type_name == nullptr);
        verify(inside_1_rfx->size == sizeof(example.inside_1));
        verify(inside_1_rfx->offset == offsetof(struct example, inside_1));

        verify(inside_1_rfx->fields != nullptr);
        field_rfx = inside_1_rfx->fields + 0;
        verify(field_rfx->type == POINTER);
        verify(str_equal(field_rfx->name, string("number_ptr")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(void*));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.number_ptr) - offsetof(struct example, inside_1));

        field_rfx = inside_1_rfx->fields + 1;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("number")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.number) - offsetof(struct example, inside_1));

        struct reflection* inside_2_rfx = inside_1_rfx->fields + 2;
        verify(inside_2_rfx->type == STRUCT);
        verify(str_equal(inside_2_rfx->name, string("inside_2")));
        verify(inside_2_rfx->type_name == nullptr);
        verify(inside_2_rfx->size == sizeof(example.inside_1.inside_2));
        verify(inside_2_rfx->offset ==
          offsetof(struct example, inside_1.inside_2) - offsetof(struct example, inside_1));

        verify(inside_2_rfx->fields != nullptr);
        field_rfx = inside_2_rfx->fields + 0;
        verify(field_rfx->type == POINTER);
        verify(str_equal(field_rfx->name, string("number_ptr")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(void*));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.inside_2.number_ptr) -
          offsetof(struct example, inside_1.inside_2));

        field_rfx = inside_2_rfx->fields + 1;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("number")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.inside_2.number) -
          offsetof(struct example, inside_1.inside_2));

      success();
    } end();

  } end();

  when("reflecting a list container") {
    when("the list reflection has no limits") {
      list<struct squadmate> squad;

      struct reflection rfx = reflect(list<struct squadmate>, CONTAINER, of(
        reflect(struct squadmate, STRUCT, fields(
          field(struct squadmate, STR,  name),
          field(struct squadmate, ENUM, class),
          field(struct squadmate, INT,  health),
          field(struct squadmate, INT,  shields),
        ))),
        container(list, struct squadmate)
      );

      must("correctly define the reflection");
        verify(rfx.type == CONTAINER);
        verify(str_empty(rfx.name));
        verify(cstr_equal(rfx.type_name, "list_struct_squadmate"));
        verify(rfx.size == sizeof(squad));
        verify(rfx.container.creator == list<struct squadmate>_reflection_creator);
        verify(rfx.container.adder == list<struct squadmate>_reflection_adder);

        verify(rfx.element != nullptr);
        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == STRUCT);
        verify(str_empty(element_rfx->name));
        verify(cstr_equal(element_rfx->type_name, "struct squadmate"));
        verify(element_rfx->size == sizeof(struct squadmate));
        verify(element_rfx->offset == 0);

        verify(element_rfx->fields != nullptr);
        struct reflection* field_rfx;
        field_rfx = element_rfx->fields + 0;
        verify(field_rfx->type == STR);
        verify(str_equal(field_rfx->name, string("name")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(str));
        verify(field_rfx->offset == offsetof(struct squadmate, name));

        field_rfx = element_rfx->fields + 1;
        verify(field_rfx->type == ENUM);
        verify(str_equal(field_rfx->name, string("class")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(enum classes));
        verify(field_rfx->offset == offsetof(struct squadmate, class));

        field_rfx = element_rfx->fields + 2;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("health")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct squadmate, health));

        field_rfx = element_rfx->fields + 3;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("shields")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct squadmate, shields));

      success();
    } end();

    /*
    when("the list reflection has limits") {
      list<struct squadmate> squad;

      struct reflection rfx = {
        type(LIST), limited_to(4, 8), of({
          type(STRUCT, struct squadmate), fields({
            { field(name, STR, struct squadmate) },
            { field(class, ENUM, struct squadmate) },
            { field(health, INT, struct squadmate) },
            { field(shields, INT, struct squadmate) },
          }),
        }),
      };

      must("correctly define the reflection");
        verify(rfx.type == LIST);
        verify(str_empty(rfx.name));
        verify(rfx.type_name == nullptr);
        verify(rfx.size == sizeof(squad));
        verify(rfx.size_limits.min == 4);
        verify(rfx.size_limits.max == 8);
        verify(rfx.offset == 0);
        verify(rfx.element != nullptr);

        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == STRUCT);
        verify(str_empty(element_rfx->name));
        verify(cstr_equal(element_rfx->type_name, "struct squadmate"));
        verify(element_rfx->size == sizeof(struct squadmate));
        verify(element_rfx->offset == 0);
        verify(element_rfx->fields != nullptr);
        verify(element_rfx->fields->length == 4);

        struct reflection* field_rfx;
        field_rfx = element_rfx->fields + 0;
        verify(field_rfx->type == STR);
        verify(str_equal(field_rfx->name, string("name")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(str));
        verify(field_rfx->offset == offsetof(struct squadmate, name));

        field_rfx = element_rfx->fields + 1;
        verify(field_rfx->type == ENUM);
        verify(str_equal(field_rfx->name, string("class")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(enum classes));
        verify(field_rfx->offset == offsetof(struct squadmate, class));

        field_rfx = element_rfx->fields + 2;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("health")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct squadmate, health));

        field_rfx = element_rfx->fields + 3;
        verify(field_rfx->type == INT);
        verify(str_equal(field_rfx->name, string("shields")));
        verify(field_rfx->type_name == nullptr);
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct squadmate, shields));

      success();
    } end();

    when("the list type is nested") {
      list<list<int>> table;

      struct reflection rfx = {
        type(LIST), of({
          type(LIST), of({
            type(INT)
          }),
        }),
      };

      must("correctly define the reflection");
        verify(rfx.type == LIST);
        verify(rfx.size == sizeof(table));
        verify(str_empty(rfx.name));
        verify(rfx.type_name == nullptr);
        verify(rfx.offset == 0);
        verify(rfx.element != nullptr);

        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == LIST);
        verify(str_empty(element_rfx->name));
        verify(element_rfx->type_name == nullptr);
        verify(element_rfx->size == sizeof(list<int>));
        verify(element_rfx->offset == 0);
        verify(element_rfx->element != nullptr);

        element_rfx = element_rfx->element;
        verify(element_rfx->type == INT);
        verify(str_empty(element_rfx->name));
        verify(element_rfx->type_name == nullptr);
        verify(element_rfx->size == sizeof(int));
        verify(element_rfx->offset == 0);

      success();
    } end();
  */
  } end();
}
