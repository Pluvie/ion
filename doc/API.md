<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## API

[allocator_init](#allocator-init)

### Allocator

#### allocator init

```c
struct allocator allocator_init (
    uint capacity
);
```

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
