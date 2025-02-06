<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Reflection

__Ion__ provides a reflection mechanism to describe program objects using the source
code itself.

Reflection is basically a description of a program object in terms of:

  - type: which is the type of object? integer, decimal, struct, pointer, array, etc.
  - type size: the size in bytes of the object.
  - fields: for struct types, which are its fields?
  - constraints: for example, in array types, is there a maximum or minimum length?

The starting point with reflection is the `struct reflect`. To help initialize its
values, __Ion__ provides a series of useful macros which shall be covered in this
chapter.

Let's begin by describing a simple integer:

```c
i8 number = 7;
struct reflect number_reflection = { type(I8) };
```

All primitive types can be reflected using the appropriate type constant:

| Type | Constant |
|------|----------|
| u8   | U8       |
| u16  | U16      |
| u32  | U32      |
| u64  | U64      |
| i8   | I8       |
| i16  | I16      |
| i32  | I32      |
| i64  | I64      |
| d32  | D32      |
| d64  | D64      |
| d128 | D128     |
| bool | BOOL     |
| byte | BYTE     |
| char | CHAR     |

Struct types can be reflected using the type `STRUCT` and the macro `fields` and `field`:

```c
struct point {
   d64 x;
   d64 y;
};

struct reflect point_reflection = {
  type(STRUCT, sizeof(struct point), fields({
    { field(struct point, x), type(D64) },
    { field(struct point, y), type(D64) },
  })
};
```

## Object

Every object in the program has its memory address where its data is stored. Consider
the following variable:

```c
struct array numbers = array_of(i8, { 7, 8, 9 });
```

This variable is an object in the program: its has a name -- "numbers" --, an address --
`&numbers` in C language --, a type -- `struct array` --, and an associated value.

Using __Ion__ reflection we can set up a reflection for this object:

```c
struct reflect numbers_reflection = { type(ARRAY), of({ type(I8) }) };
```

__Ion__ then provides the `struct object` to completely describe this program object,
using all the information above:

```c
struct object numbers_object = {
  .name = "numbers",
  .address = &numbers,
  .reflection = numbers_reflection,
  .allocator = NULL,
};
```

Using this `numbers_object` we can know everything about the `numbers` real object in
the program and use the source code itself to work with its resources.
