/**
 * @file
 * ### Macros
 *
 * This file defines all macros provided with Ion. */




/**
 * Padding for structs. */
#define padding(amount) \
  byte __padding[amount];




/**
 * Tells the compiler that the "true" branch of this condition is likely to happen,
 * so the code prefetching in the CPU pipeline shall be loaded with the "true" branch,
 * in order to gain speed. */
#define likely(x) \
  __builtin_expect(!!(x), 1) 

/**
 * Tells the compiler that the "false" branch of this condition is likely to happen,
 * so the code prefetching in the CPU pipeline shall be loaded with the "false" branch,
 * in order to gain speed. */
#define unlikely(x) \
  __builtin_expect(!!(x), 0)




/**
 * Check a condition at compile time.
 *
 * Example:
 *
 * ```c
 * compile_time_check(EXAMPLE_CONSTANT == 42,
 *   "the constant EXAMPLE_CONSTANT must be equal to 42");
 * ```
 *
 * If the *condition* evaluates to false, then a compile error is thrown, which prints
 * the provided *message*. */
#define compile_time_check(condition, message) \
  _Static_assert(condition, message)

/**
 * Layer of macro indirection to make the #compile_concat macro work. */
#define compile_concat_indirect(prefix, suffix) \
  prefix ## suffix
/**
 * Concatenates two preprocessor tokens. */
#define compile_concat(prefix, suffix) \
  compile_concat_indirect(prefix, suffix)

/**
 * Check the bytesize of a *type* at compile time.
 *
 * Example:
 *
 * ```c
 * check_sizeof(ExampleType, 1024);
 * ```
 *
 * If the bytesize of the given *type* does not match the given *bytesize*,
 * throws a compile error. */
#define check_sizeof(type, bytesize) \
  compile_time_check(sizeof(type) == bytesize, \
    #type " must have size of " #bytesize " bytes");

/**
 * Prints a fake compile time error which shows the bytesize of a *type*.
 *
 * The error is totally fake, it just helps to know the exact bytesize of a type,
 * after the compiler has done potential paddings. */
#define print_sizeof(type) \
  char __fake_var[sizeof(type)] = { __fake_error(&__fake_var) };

char __fake_error(int);




/**
 * Generates a unique variable name using the line number. */
#define lvar(name) \
  compile_concat(name, __LINE__)

/**
 * Generates a unique variable name using the global counter number. */
#define cvar(name) \
  compile_concat(name, __COUNTER__)




/**
 * Computes the number of elements of a stack allocated array.
 *
 * Example:
 *
 * ```c
 * u64 numbers[11];
 * countof(numbers); // 11, because sizeof(numbers) = 88, sizeof(u64) = 8, 88 / 8 = 11
 * ```
 *
 * This macro does not work with pointer types. The argument *array* must be a stack
 * allocated array, with fixed length. */
#define countof(array) \
  (sizeof(array) / sizeof(*(array)))

/**
 * Same of #countof, but minus `1`.
 *
 * Useful for loops starting from `1`. */
#define lengthof(array) \
  (countof(array) - 1)

/**
 * Retrieves the value of the given `void*` *pointer* casted to the given *type*. */
#define as(type, pointer) \
  (*(type*) (pointer))




/**
 * Helper to create a string from double quoted literal. */
#define s(str) \
  (struct string) { .content = str, .length = sizeof(str) - 1 }

/**
 * Helper to test the equality of two strings. */
#define streq(s1, s2) \
  (strcmp(s1, s2) == 0)

/**
 * Helper to test the equality of two strings, case insensitive. */
#define strcaseeq(s1, s2) \
  (strcasecmp(s1, s2) == 0)

/**
 * Helper to test the equality of two strings, with a maximum size. */
#define strneq(s1, s2, n) \
  (strncmp(s1, s2, n) == 0)

/**
 * Helper to test the equality of two strings, case insensitive, with a maximum size. */
#define strncaseeq(s1, s2, n) \
  (strncasecmp(s1, s2, n) == 0)

/**
 * Helper to test the equality of two memory regions. */
#define memeq(s1, s2, n) \
  (memcmp(s1, s2, n) == 0)




/**
 * Computes the logarithm in base `2` of a *number*.
 *
 * The computation is done using compiler builtins, specifically [__builtin_clzl](
 * https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html) which are fast and efficient
 * operation on CPU registers. */
#define log2(number) \
  (number > 1 ? 64 - __builtin_clzl((u64) number - 1) : 0)

/**
 * Calculates the next power of `2` starting from *number*.
 *
 * If the *number* is already a power of `2`, this macro is idempotent. */
#define next_pow2(number) \
  (1 << log2(number))

/**
 * Determines if *number* is a power of `2`.
 *
 * If the number is `0` or less, this macro results always in `false`, otherwise it
 * results `true` if the number is a power of `2` and `false` in the other cases. */
#define is_pow2(number) \
  (number > 0 ? (number & (number - 1)) == 0 : false)

/**
 * Determines if two decimal numbers are approximately equal. */
#define approx_eq(d1, d2) \
  (fabsl((d128) ((d1) - (d2))) < epsilon)




/**
 * Used to reference another previously defined protocol schema to handle a struct. */
#define schema(schema_name)             \
  .type = STRUCT,                       \
  .child = (schema_name)->child,        \
  .bounds = {                           \
    (schema_name)->bounds[0],           \
    (schema_name)->bounds[1]            \
  }

/**
 * Used to define a type of a protocol schema. */
#define type(type_name, ...)            \
  .type = type_name __VA_OPT__(, .bounds = __VA_ARGS__, .child = (struct reflect []))

/**
 * Used to define a struct field in a protocol schema. */
#define field(field_name, struct_name)  \
  .offset = offsetof(struct_name, field_name), .name = #field_name




/**
 * Set a failure with the given printf-like *format* string. */
#define failure(f, format, ...) { \
  (f)->occurred = true;           \
  (f)->length = snprintf(         \
    (f)->message,                 \
    sizeof((f)->message),         \
    format,                       \
    ##__VA_ARGS__);               \
}




/**
 * Emits a text *message* to screen. Does not go to a new line. */
#define emit(message, ...)                      \
  fprintf(stderr, message, ##__VA_ARGS__)

/**
 * Emits a text *message* with the provided *color* to screen. Does not go to a new
 * line. */
#define emit_c(color, message, ...) {           \
  fprintf(stderr, color);                       \
  fprintf(stderr, message, ##__VA_ARGS__);      \
  fprintf(stderr, PRINT_COLOR_NONE); }

/**
 * Prints a text *message* to screen. Goes to a new line. */
#define print(message, ...)                     \
  fprintf(stderr, message "\n", ##__VA_ARGS__)

/**
 * Prints a text *message* with the provided *color* to screen. Goes to a new line. */
#define print_c(color, message, ...) {          \
  fprintf(stderr, color);                       \
  fprintf(stderr, message "\n", ##__VA_ARGS__); \
  fprintf(stderr, PRINT_COLOR_NONE); }




/**
 * Initializes an io reader (with flag #IO_READ) on the specified data with the
 * specified length. */
#define io_reader(data_var, length_var)       \
  (struct io) { .data = (byte*) data_var,     \
    .length = length_var,                     \
    .flags = IO_READ }

/**
 * Initializes an io writer (with flag #IO_WRITER) on the specified data with the
 * specified length. Optionally gives an allocator to dynamically resize the data. */
#define io_writer(data_var, length_var, ...)  \
  (struct io) { .data = (byte*) data_var,     \
    .length = length_var,                     \
    .flags = IO_WRITE,                        \
    __VA_OPT__(, .allocator = __VA_ARGS__) }

/**
 * Checks if the io cursor has reached the io length. */
#define io_exhausted(io) \
  ((io)->cursor == (io)->length)




/**
 * Creates an array literal. */
#define arrayof(type, ...)                                    \
  { .typesize = sizeof(type),                                 \
    .data = (type []) __VA_ARGS__,                            \
    .length = sizeof((type []) __VA_ARGS__) / sizeof(type) }




/**
 * Loops through the keys and values of a map. */
#define map_each(map, key, val)                                         \
  (void* key = NULL; key != (void*) 1; key = (void*) 1)                 \
    for (void* val = NULL; val != (void*) 1; val = (void*) 1)           \
      for (u64 i = 0; i < (map)->capacity + log2((map)->capacity); i++) \
        if (key = (byte*) (map)->keys + (i * (map)->key_typesize),      \
            val = (byte*) (map)->values + (i * (map)->value_typesize),  \
            (map)->hashes[i] != -1)

