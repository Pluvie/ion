<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## API

```c
struct arena    /* Regional memory allocator. */
```
Type:
  - [arena](#arena)

API:
  - [arena_create](#arena-create)
  - [arena_destroy](#arena-destroy)
  - [arena_push](#arena-push)

---

```c
struct buffer   /* Linear memory allocator. */
```
Type:
  - [buffer](#buffer)

API:
  - [buffer_address](#buffer-address)
  - [buffer_address_at](#buffer-address-at)
  - [buffer_init](#buffer-init)

---

```c
cstr            /* String, always null terminated. */
```
Type:
  - [cstr](#cstr)

API:
  - [cstr_compare](#cstr-compare)
  - [cstr_equal](#cstr-equal)

---

```c
str             /* String, with incorporated length, may be not null terminated. */
```
Type:
  - [str](#str)

API:
  - [str_append](#str-append)
  - [str_compare](#str-compare)
  - [str_compare_case](#str-compare-case)
  - [str_empty](#str-empty)
  - [str_equal](#str-equal)
  - [str_equal_case](#str-equal-case)
  - [str_strip](#str-strip)
  - [str_to_int](#str-to-int)
  - [str_to_dec](#str-to-dec)

---

### arena

```c
struct arena
```
The `struct arena` is a memory allocator. It is used to group together pointers that
share the same **lifetime** across a program.

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

---

### arena create

```c
struct arena arena_create (
    uint capacity
);
```

#### Description

This function creates a `struct arena` with the given *capacity*. It does not perform
any allocation yet, but the returned arena is ready to allocate memory using
[arena_push](#arena-push).

#### Return Value

A `struct arena` with the given *capacity*.

#### Errors

This function never fails.

---

### arena destroy

```c
void arena_destroy (
    struct arena* allocator
);
```

#### Description

This function shall release all the memory, allocated by *allocator*, back to the
operating system, and shall zero out the entire *allocator* struct. All pointers
that were returned by calls to the [arena_push](#arena-push) function, on this
*allocator*, must be considered invalid.

This function should be called when the lifetime of all pointers allocated on the arena
*allocator* is ended, and therefore the program does not need its memory anymore.

#### Return Value

None.

#### Errors

This function never fails.

---

### arena push

```c
void* arena_push (
    struct arena* allocator,
    uint amount
);
```

#### Description

This function allocates a given `uint` *amount* of bytes on the given `struct arena`
*allocator*.

The *allocator* ensures to automatically grow its capacity in order to fit the required
*amount* of memory. This operation is transparent to the caller. The returned pointer
is guaranteed to be always valid across the entire life of the *allocator* -- i.e. up
until a call to [arena_destroy](#arena-destroy) is made.

#### Return Value

A pointer to the first available address in the *allocator* memory, after having made
enough space for it.

#### Errors

This function never fails.

In order to accomodate this call, the allocator may request memory to the operating
system. If the system is out of memory, or is either way unable to fulfill the
request, then this function shall [abort](
https://www.man7.org/linux/man-pages/man3/abort.3.html) the entire program.

---

### buffer

A `struct buffer` is a memory allocator. It is best used to when a program requires a
contiguous amount of memory, which can also be dynamically increased.

Imagine parsing a chunked HTTP response: you do not know how long the full response
will be; instead you receive it in chunks. Each chunk starts with a number that
indicates how many bytes the chunk content will be. You also want the final response
data to be contiguous in memory so that it is addressable by just a pointer and
therefore easy to pass it around to other functions which may, for example, parse it as
HTML, JSON, or something like that.

This is not a good case for the `struct arena` because of its memory fragmentation.
Even though each call to [arena_push](#arena-push) is guaranteed to return an always
valid address, it may not be adjacent to addresses returned by previous calls to the
same function.

Instead, a `struct buffer`, guarantees that every call to [buffer_push](#buffer-push)
produces contiguous addresses. However, in order to do so, it must invalidate all
previously returned addresses. Therefore, in order to keep track of memory allocated in
a `struct buffer`, one must use its position, which is guaranteed to be always valid,
using [buffer_position_get](#buffer-position-get).

A `struct buffer` is inherently **non thread-safe** due to the fact that allocating
memory is not an atomic operation. To be safely used in a multi threaded scenario,
you must use a mutex to synchronize the [buffer_push](#buffer-push) calls so that only
one thread can complete this call at once.

---

### buffer create

```c
struct buffer buffer_create (
    uint capacity
);
```

#### Description

This function creates a `struct buffer` with the given *capacity*. It does not perform
any allocation yet, but the returned buffer is ready to allocate memory using
[buffer_push](#buffer-push).

#### Return Value

A `struct buffer` with the given *capacity*.

#### Errors

This function never fails.

---

### buffer destroy

```c
void buffer_destroy (
    struct buffer* buffer
);
```

---

### buffer pointer

```c
void* buffer_pointer (
    struct buffer* allocator
);
```

#### Description

This function returns the address of the first available space in the given
`struct buffer` *allocator*.

This pointer **is not** guaranteed to be always valid: it should be discarded as soon
as another call to [buffer_push](#buffer-push) is made.

This is due to the design of the linear memory management, where memory is guaranteed to
be contiguous, but intermediate addresses returned by each [buffer_push](#buffer-push)
call might lose validity due to the internal reallocations.

#### Return Value

A pointer to the first available space in the buffer memory.

#### Errors

This function never fails.

---

### buffer pointer at

```c
void* buffer_pointer_at (
    struct buffer* allocator,
    uint position
);
```

#### Description

This function returns the address of the given `struct buffer` *allocator* at the
given *position*.

The *position* value is assumed to be in bytes. The returned address **is not**
guaranteed to be always valid: it should be discarded as soon as another call to
[buffer_push](#buffer-push) is made.

This is due to the design of the linear memory management, where memory is guaranteed to
be contiguous, but intermediate addresses returned by each [buffer_push](#buffer-push)
call might lose validity due to the internal reallocations.

#### Return Value

A pointer to the buffer memory with a byte offset equal to *position*.

#### Errors

This function never fails.

If the *position* is greater than the buffer current position, this function shall
[abort](https://www.man7.org/linux/man-pages/man3/abort.3.html) the program.

---

### buffer position get

```c
uint buffer_position_get (
    struct buffer* buffer
);
```

---

### buffer position set

```c
void buffer_position_set (
    struct buffer* buffer,
    uint position
);
```

---

### buffer push

```c
void* buffer_push (
    struct buffer* allocator,
    uint amount
);
```
