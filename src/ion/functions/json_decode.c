static inline void json_decode_array (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_array_as_array (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_array_as_list (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_array_as_set (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_false (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_null (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_number (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_number_as_dec (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_number_as_int (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_object (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_object_as_struct (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_object_as_map (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_string (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_true (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_value (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_discard_array (
    str* source
);

static inline void json_discard_object (
    str* source
);

static inline void json_discard_number (
    str* source
);

#define json_advance(source, amount)          source->chars += amount
#define json_contains(source, value, length)  memory_equal(source->chars, value, length)
#define json_cursor(source)                   (source->chars)
#define json_exhausted(source)                (*(source->chars) == 0)

#define json_parse_array    json_decode_array(source, target, reflection, allocator)
#define json_parse_false    json_decode_false(source, target, reflection)
#define json_parse_null     json_decode_null(source, target, reflection)
#define json_parse_number   json_decode_number(source, target, reflection)
#define json_parse_object   json_decode_object(source, target, reflection, allocator)
#define json_parse_string   json_decode_string(source, target, reflection)
#define json_parse_true     json_decode_true(source, target, reflection)
#define json_parse_value    json_decode_value(source, target, reflection, allocator)

void json_decode (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  printl();
  char* source_begin = source->chars;
  json_decode_value(source, target, reflection, allocator);

  if (unlikely(failure.occurred)) {
    char error[1024] = { 0 };
    unsigned int position = source->chars - source_begin;
    printl(">>>>>>> position: ", f(position));
    memory_copy(error, source_begin, source->length);
    error[position] = '@';
    fail("json error: ", failure.message, "\n", error);
  }
}

static inline void json_decode_array (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  if (reflection == nullptr)
    return json_discard_array(source);

  if (reflection->type == ARRAY)
    return json_decode_array_as_array(source, target, reflection, allocator);

  if (reflection->type == LIST)
    return json_decode_array_as_list(source, target, reflection, allocator);

  if (reflection->type == SET)
    return json_decode_array_as_set(source, target, reflection, allocator);

  fail("incompatible reflection type");
  return;
}

static inline void json_decode_array_as_array (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
}

static inline void json_decode_array_as_list (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
}

static inline void json_decode_array_as_set (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  struct reflection* set_element_reflection = reflection->element;
  void* set_element_target = allocator_push(allocator, set_element_reflection->size);

  #define json_parse_array_init \
    reflection->container.creator(target, 8, allocator);

  #define json_parse_array_member \
    json_decode_value(source, set_element_target, set_element_reflection, allocator); \
    reflection->container.adder(target, set_element_target);

  #include "../procedures/json_parse_array.c"
  #undef json_parse_array_init
  #undef json_parse_array_member
}

static inline void json_discard_array (
    str* source
)
{
  #define json_parse_array_init
  #define json_parse_array_member json_decode_value(source, nullptr, nullptr, nullptr)
  #include "../procedures/json_parse_array.c"
  #undef json_parse_array_init
  #undef json_parse_array_member
}

static inline void json_decode_true (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  if (reflection == nullptr)
    return;

  if (reflection->type != BOOL) {
    fail("incompatible reflection type");
    return;
  }

  memory_copy(target, &(bool) { true }, sizeof(bool));
}

static inline void json_decode_false (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  if (reflection == nullptr)
    return;

  if (reflection->type != BOOL) {
    fail("incompatible reflection type");
    return;
  }

  memory_copy(target, &(bool) { false }, sizeof(bool));
}

static inline void json_decode_null (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  if (reflection == nullptr)
    return;

  memory_set(target, 0, reflection->size);
}

static inline void json_decode_number (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  if (reflection == nullptr)
    return json_discard_number(source);

  if (reflection->type == DEC)
    return json_decode_number_as_dec(source, target, reflection);

  if (reflection->type == INT)
    return json_decode_number_as_int(source, target, reflection);

  fail("incompatible reflection type");
  return;
}

static inline void json_discard_number (
    str* source
)
{
  #define cursor source->chars
  #define PARSE_NUMBER__DISCARD
  #include "../procedures/parse_number.c"
  #undef  PARSE_NUMBER__DISCARD
  #undef  cursor

procedure_success:
  return;

procedure_failure:
  return;
}

static inline void json_decode_number_as_dec (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  dec result = 0;

  #define cursor source->chars
  #define PARSE_NUMBER__DECIMAL
  #include "../procedures/parse_number.c"
  #undef  PARSE_NUMBER__DECIMAL
  #undef  cursor

procedure_success:
  *(dec*) target = result;

procedure_failure:
  return;
}

static inline void json_decode_number_as_int (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  int result = 0;

  #define cursor source->chars
  #define PARSE_NUMBER__INTEGER
  #include "../procedures/parse_number.c"
  #undef  PARSE_NUMBER__INTEGER
  #undef  cursor

procedure_success:
  *(int*) target = result;

procedure_failure:
  return;
}

static inline void json_decode_object (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  if (reflection == nullptr)
    return json_discard_object(source);

  if (reflection->type == STRUCT)
    return json_decode_object_as_map(source, target, reflection, allocator);

  if (reflection->type == MAP &&
      reflection->element != nullptr &&
      reflection->element->type == STR)
    return json_decode_object_as_map(source, target, reflection, allocator);

  fail("incompatible reflection type");
  return;
}

static inline void json_discard_object (
    str* source
)
{
  #define json_parse_object_init
  #define json_parse_object_member_name
  #define json_parse_object_member_value \
    json_decode_value(source, nullptr, nullptr, nullptr);
  #include "../procedures/json_parse_object.c"
  #undef json_parse_object_init
  #undef json_parse_object_member_name
  #undef json_parse_object_member_value
}

static inline void json_decode_object_as_map (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  struct reflection* map_value_reflection = reflection->element->element;
  void* map_value_target = nullptr;

  #define json_parse_object_init \
    reflection->container.creator(target, 8, allocator);

  #define json_parse_object_member_name \
    map_value_target = reflection->container.adder(target, &object_member_name);

  #define json_parse_object_member_value \
    json_decode_value(source, map_value_target, map_value_reflection, allocator);

  #include "../procedures/json_parse_object.c"

  #undef json_parse_object_init
  #undef json_parse_object_member_name
  #undef json_parse_object_member_value
}

static inline void json_decode_object_as_struct (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  struct reflection* field_reflection = nullptr;
  void* field_target = nullptr;

  #define json_parse_object_init
  #define json_parse_object_member_name                                                 \
    field_reflection = reflection_field_find(reflection, &object_member_name);          \
    if (field_reflection != nullptr) {                                                  \
      field_target = target + field_reflection->offset;                                 \
    }
  #define json_parse_object_member_value \
    json_decode_value(source, field_target, field_reflection, allocator)

  #include "../procedures/json_parse_object.c"

  #undef json_parse_object_init
  #undef json_parse_object_member_name
  #undef json_parse_object_member_value
}

static inline void json_decode_string (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  str result = { 0 };
  #include "../procedures/json_parse_string.c"

  if (reflection == nullptr)
    return;

  if (reflection->type != STR) {
    fail("incompatible reflection type");
    return;
  }

  *(str*) target = result;
  reflection_validate(target, reflection);
}

static inline void json_decode_value (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  #include "../procedures/json_parse_value.c"
}

#undef json_parse_array
#undef json_parse_false
#undef json_parse_null
#undef json_parse_number
#undef json_parse_object
#undef json_parse_string
#undef json_parse_true
#undef json_parse_value

#undef json_advance
#undef json_contains
#undef json_cursor
#undef json_exhausted
