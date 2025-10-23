void str_build (
    struct str_builder* builder,
    str value
)
{
  if (builder->result.length + value.length > builder->capacity) {
    unsigned int increased_capacity = 2 * builder->capacity;
    builder->memory = memory_resize(builder->memory, increased_capacity);
    builder->capacity = increased_capacity;
  }

  memory_copy(builder->memory + builder->result.length, value.chars, value.length);
  builder->result.chars = builder->memory;
  builder->result.length += value.length;
}
