/*
  Defines all internal functions used by the JSON decoding suite.
*/

#define json_advance(source, amount)          source->chars += amount
#define json_contains(source, value, length)  memory_equal(source->chars, value, length)
#define json_cursor(source)                   (source->chars)
#define json_exhausted(source)                (*(source->chars) == 0)
#define json_parse_spaces(source)             json_discard_spaces(source)




/*
  JSON arrays can be decoded into C array, list or set targets.
*/

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
  struct reflection* array_element_reflection = reflection->element;
  void* array_element_target = nullptr;
  int array_element_index = 0;
  unsigned int array_max_index = reflection->size / array_element_reflection->size;
  unsigned int array_element_position = 0;

  #include "../procedures/json_parse_array.c"

init_callback:
  goto init_resume;

member_callback:
  if (array_element_index < array_max_index) {
    array_element_position = array_element_index * array_element_reflection->size;
    array_element_target = target + array_element_position;
    json_decode_value(source, array_element_target, array_element_reflection, allocator);
    array_element_index++;
    goto member_resume;
  }

  fail("array maximum size is ", f(array_max_index));
  return;
}

static inline void json_decode_array_as_list (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  struct reflection* list_element_reflection = reflection->element;
  void* list_element_target = allocator_push(allocator, list_element_reflection->size);

  #include "../procedures/json_parse_array.c"

init_callback:
  reflection->container.creator(target, 8, allocator);
  goto init_resume;

member_callback:
  json_decode_value(source, list_element_target, list_element_reflection, allocator);
  reflection->container.adder(target, list_element_target);
  goto member_resume;
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

  #include "../procedures/json_parse_array.c"

init_callback:
  reflection->container.creator(target, 8, allocator);
  goto init_resume;

member_callback:
  json_decode_value(source, set_element_target, set_element_reflection, allocator);
  reflection->container.adder(target, set_element_target);
  goto member_resume;
}

static inline void json_discard_array (
    str* source
)
{
  #include "../procedures/json_parse_array.c"

init_callback:
  goto init_resume;

member_callback:
  json_decode_value(source, nullptr, nullptr, nullptr);
  goto member_resume;
}




/*
  JSON literal true, false can be decoded on C bool targets.
  JSON literal null can be decoded to anything: it zero initializes the corresponding
  C value.
*/

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




/*
  JSON numbers can be decoded to C int, dec or enum targets.
*/

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

  if (reflection->type == ENUM)
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




/*
  JSON objects can be decoded to C structs or map (with a str key) targets.
*/

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
    return json_decode_object_as_struct(source, target, reflection, allocator);

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
  #include "../procedures/json_parse_object.c"

init_callback:
  goto init_resume;

member_key_callback:
  goto member_key_resume;

member_value_callback:
  json_decode_value(source, nullptr, nullptr, nullptr);
  goto member_value_resume;
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

  #include "../procedures/json_parse_object.c"

init_callback:
  reflection->container.creator(target, 8, allocator);
  goto init_resume;

member_key_callback:
  map_value_target = reflection->container.adder(target, &object_member_name);
  goto member_key_resume;

member_value_callback:
  json_decode_value(source, map_value_target, map_value_reflection, allocator);
  goto member_value_resume;
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

  #include "../procedures/json_parse_object.c"

init_callback:
  goto init_resume;

member_key_callback:
  field_reflection = reflection_field_find(reflection, &object_member_name);
  if (field_reflection != nullptr) {
    field_target = target + field_reflection->offset;
  }
  goto member_key_resume;

member_value_callback:
  json_decode_value(source, field_target, field_reflection, allocator);
  goto member_value_resume;
}




/*
  JSON strings can be decoded to C enum or string targets.
  For enums, the reflection must specify the enumerator function.
*/

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




/*
  JSON spaces are just discarded.
*/

static inline void json_discard_spaces (
    str* source
)
{
  #include "../procedures/json_parse_spaces.c"
}




/*
  This function is a catch-all for all JSON values. It shall begin the parsing and,
  depending on the value of the first meaningful character found on the source, it
  shall call the matching json_decode_* function.
*/

static inline void json_decode_value (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  #define json_parse_array    json_decode_array(source, target, reflection, allocator)
  #define json_parse_false    json_decode_false(source, target, reflection)
  #define json_parse_null     json_decode_null(source, target, reflection)
  #define json_parse_number   json_decode_number(source, target, reflection)
  #define json_parse_object   json_decode_object(source, target, reflection, allocator)
  #define json_parse_string   json_decode_string(source, target, reflection)
  #define json_parse_true     json_decode_true(source, target, reflection)
  #define json_parse_value    json_decode_value(source, target, reflection, allocator)

  #include "../procedures/json_parse_value.c"

  #undef json_parse_array
  #undef json_parse_false
  #undef json_parse_null
  #undef json_parse_number
  #undef json_parse_object
  #undef json_parse_string
  #undef json_parse_true
  #undef json_parse_value
}

#undef json_advance
#undef json_contains
#undef json_cursor
#undef json_exhausted
#undef json_parse_spaces
