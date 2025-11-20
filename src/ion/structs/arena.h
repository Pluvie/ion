struct arena {
  byte* data;
  uint capacity;
  uint position;
  struct {
    void** addresses;
    uint capacity;
    uint count;
  } regions;
};
/*
A `struct arena` is a memory allocator. It is used to group together pointers that share
the same **lifetime** across a program.

Imagine a web request, a videogame frame, or a UI screen: all these situations require
a lot of data to be readily accessible from memory in order for the program to work
correctly. However, the same data may well not be required anymore when the situation
changes: in case of the the web request because it is completed, the videogame frame
because the player has changed area, or the UI screen because a user interaction has
changed the view.

So, how can we manage all this data and its required memory? The standard approach of C
programmers, and what it is unfortunately still taught in academia, is to use the
`malloc` and `free` APIs to allocate, and eventually release, these pointers. This
requires the programmer to individually keep track of each pointer and remember when
its lifetime ends. This has created, over the years, the false belief that "*memory
management in C is hard to do and very error prone*". Well, if it's indeed done like
this, we cannot do anything but agree. Fortunately, this is not something intrinsically
tied to C itself, but rather to its misuse of the basic memory management APIs. C is a
simple language, and offers barebone constructs which you can use to build increasingly
complex applications. As much as no one would do logging by explicitly calling `fprintf`
every time, one must not treat memory with only its primitive functions, but rather
create something akin to what a log library would do for logging: this is what the
`struct arena` does.

The `struct arena` follows the arena memory management approach. Read this [article
by Ryan Fleury](https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator) for
a very nice and in-depth explanation of the arena. The core concept here is: everything
is loaded into a specific arena allocator, which automatically grows the required
memory in order to satisfy the program needs. When the allocated data is no longer
needed, a single release call to the allocator is sufficient to release it all.

In order to use a `struct arena` allocator, it must be created and initialized to a
given capacity with the [arena_create](#arena-init) function. The returned allocator can
then be passed to the [arena_push](#arena-push) function to do the actual memory
allocation. This shall reserve some space in the allocator and consequently reduce the
remaining capacity. When a call to [arena_push](#arena-push) requires more memory than
the remaining capacity, then the allocator shall automatically extend it in order to
accomodate the request. The extension is transparent to the caller, and the allocator
guarantees that all returned pointers shall remain always valid.

When the user is done using the allocator, he may release all its memory at once by
calling the function [arena_destroy](#arena-destroy). After this call, all data that
was stored in the allocator, and all pointers returned by the [arena_push](#arena-push)
calls, are no longer valid.

A `struct arena` is inherently **non thread-safe** due to the fact that allocating
memory is not an atomic operation. To be safely used in a multi threaded scenario,
you must use a mutex to synchronize the [arena_push](#arena-push) calls so that only
one thread can complete this call at once.
*/
