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
is a memory allocator. It is used to group together pointers that share the same
**lifetime** across a program.

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

### allocator init

```c
struct allocator allocator_init (
    uint capacity
);
```

#### Description

This function initializes a `struct allocator` with the given *capacity*. It does not
perform any allocation, but the returned allocator is ready to allocate memory using
[allocator_push](#allocator-push).

#### Return Value

A `struct allocator` with the given *capacity*.

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
it shall be discarded, and it shall be returned the beginning address of the allocator
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

#### Description

This function allocates a given *amount* of bytes on the given *allocator*.

If the allocator has reached its capacity, or if the allocator did not yet perform any
allocations, then the required memory to accomodate this call is requested to the
operating system. This memory shall be then added to -- and managed by -- the allocator.

#### Return Value

A pointer to the first available address in the *allocator* memory, after having made
enough space for it. This pointer is guaranteed to be safe and always valid throughout
all the life of the allocator. All pointers returned by this function shall be
invalidated by the [allocator_release](#allocator-release) call.

#### Errors

This function never fails. If, in order to accomodate this request, the allocator must
perform a request for more memory to the operating system, and the hardware is out of
memory, then this function shall [abort](
https://www.man7.org/linux/man-pages/man3/abort.3.html).

---

### allocator-release

```c
void allocator_release (
    struct allocator* allocator
);
```

#### Description

This function shall release all the memory allocated by the given *allocator*. The
memory is returned to the operating system. All pointers returned by the
[allocator_push](#allocator-push) function shall be invalidated.

#### Return Value

None.

#### Errors

This function never fails.

---

### buffer

A `struct buffer` is a memory allocator. It is used to when a program requires a
contiguous amount of memory which can be dynamically increased.

Imagine parsing a chunked HTTP response: you do not know how long the full response
will be; instead you receive it in chunks. Each chunk starts with a number that
indicates how many bytes the chunk content will be. You also want the final response
data to be contiguous in memory so that it is addressable by just a pointer and
therefore easy to pass it around to other functions which may, for example, parse it as
HTML, JSON, or something like that.

This is not a good case for the `struct arena` because of its memory fragmentation.
Even though each call to [arena_push](#arena-push) is guaranteed to return an always
valid address, it may not be adjacent to addresses returned by previous calls to the
same function. This is by design.

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

### buffer-address

```c
void* buffer_address (
    struct buffer* buffer
);
```

#### Description

This function returns the address of the first available space in the given *buffer*.
This pointer **is not** guaranteed to be always valid: it should be discarded as soon
as a call to [buffer_push](#buffer-push) is made.

This is consistent with the linear memory management approach, where memory is
guaranteed to be contiguous, but intermediate addresses returned by each [buffer_push](
#buffer-push) call might lose validity due to the internal reallocations.

#### Return Value

A pointer to the first available space in the buffer memory.

#### Errors

This function never fails.

---

### buffer-address-at

```c
void* buffer_address_at (
    struct buffer* buffer,
    uint position
);
```

#### Description

This function returns the address of the given *buffer* space at the given *position*.
The *position* value is assumed to be in bytes. The returned address **is not**
guaranteed to be always valid: it should be discarded as soon as a call to
[buffer_push](#buffer-push) is made.

This is consistent with the linear memory management approach, where memory is
guaranteed to be contiguous, but intermediate addresses returned by each [buffer_push](
#buffer-push) call might lose validity due to the internal reallocations.

#### Return Value

A pointer to the buffer memory with a byte offset equal to *position*.

#### Errors

This function never fails. If the *position* is greater than the buffer current
position, this function shall [abort](
https://www.man7.org/linux/man-pages/man3/abort.3.html).

---

### buffer-init

```c
struct buffer buffer_init (
    uint capacity
);
```

#### Description

This function initializes a `struct buffer`.

A `struct buffer` is a linear memory allocator. The buffer is useful when a contiguous
dynamic amount of memory is required. It can be seen as an infinite stack, where each
allocation is done with [buffer_push](#buffer-push). If the buffer requires more memory
to accomodate the call, it shall request it to the operating system. Also, in order to
maintain memory contiguity, a full reallocation of the buffer may be performed. For this
reason, pointers returned by buffer allocations **are not** guaranteed to be always
valid.

#### Return Value

A `struct buffer` with the given *capacity*. No allocation is performed, but the
returned buffer is ready to allocate memory using [buffer_push](#buffer-push).
ready to allocate.

#### Errors

This function never fails.
