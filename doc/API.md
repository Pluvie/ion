<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## API

Allocator
  - [allocator_init](#allocator-init)
  - [allocator_pop](#allocator-pop)

## Allocator

### allocator init

```c
struct allocator allocator_init (
    uint capacity
);
```

#### Description

This function initializes a `struct allocator` with the given *capacity*.

A `struct allocator` is a memory allocator and tracker. It is defined as:

```c
struct allocator {
  byte* data;
  uint capacity;
  uint position;
  struct {
    void** addresses;
    uint capacity;
    uint count;
  } regions;
  struct {
    uint count;
    uint size;
  } allocations;
};
```

An allocator is used to group code objects that share the same lifetime across the
program. Imagine a web request, a videogame frame or a UI screen: all these entities
require many objects to be readily accessible from memory in order for the program to
work correctly. But these same objects may well not be required anymore when the entity
has done its job: in case of the the web request because it is completed and the
connection is closed, the videogame frame because the player has changed area, or the UI
screen because a user interaction has changed the view.

The standard approach of C programmers, and what it is still unfortunately taught in
academia, is to use the `malloc` and `free` APIs to allocate, and eventually release,
these objects. This requires the programmer to individually keep track of each object
and remember when its lifetime ends. This has created -- over the years -- the false
belief that "memory management in C is hard to do and very error prone". Well, if it is
done like this, we cannot do anything but agree. Fortunately, this is not something
intrinsically linked to C itself, but rather to its misuse of the basic memory
management APIs. C is a simple language, and offers barebone constructs which you can
use to build increasingly complex applications. As much as no one would do logging by
explicitly calling `fprintf` every time, one must not treat memory with its primitive
functions but rather create something akin to a log library would do for logging: this
is what the `struct allocator` does.

For more information and in-depth study of C memory management we strongly encourage to
read [Ryan's article](https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator)
as we feel that none has done a better job than he to explain in great detail this topic.

The `struct allocator` follows the arena memory management approach: everything is
loaded on a specific allocator, which automatically grows the required memory in order
to satisfy the program needs. When the allocated objects are not needed anymore, a
single release call to the allocator is sufficient to release them all.

#### Return Value

A `struct allocator` with the given *capacity*. No allocation is performed, but the
returned allocator is ready to allocate memory using [allocator_push](#allocator-push).

#### Errors

This function never fails.

---

### allocator pop

```c
void* allocator_pop (
    struct allocator* allocator,
    uint amount
);
```

#### Description

This function releases a given *amount* of memory from the given *allocator*.

The primary usage of a `struct allocator` is to allocate memory in chunks -- using
[allocator_push](#allocator-push) and then massively release it in one shot using
[allocator_release](#allocator-release). This is consistent with the arena memory
management principle.

However there may be some cases where some memory is not needed anymore and can be
safely released from the allocator. This function does exactly this. Note that
memory is not actually given back to the operating system, but only made available
inside the allocator.

#### Return Value

A pointer to the first available address in the *allocator* memory, after having made
enough space for it. If the *amount* is greater than the *allocator* memory, then all of
it shall be discarded and it shall be returned the beginning address of the allocator
memory.

#### Errors

This function never fails.

---

### allocator-push

```c
void* allocator_push (
    struct allocator* allocator,
    uint amount
);
```
