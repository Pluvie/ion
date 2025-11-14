<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## API

[Allocator](#allocator)

  - [allocator_init](#allocator-init)
  - [allocator_pop](#allocator-pop)
  - [allocator_push](#allocator-push)
  - [allocator_release](#allocator-release)

[Buffer](#buffer)

  - [buffer_address](#buffer-address)
  - [buffer_address_at](#buffer-address-at)
  - [buffer_init](#buffer-init)

### allocator

A `struct allocator` is a memory allocator and tracker. It is used to group code objects
that share the same lifetime across a program.

Imagine a web request, a videogame frame or a UI screen: all these situations require
many objects to be readily accessible from memory in order for the program to work
correctly. However, these same objects may well not be required anymore when the
situation changes: in case of the the web request because it is completed -- or
the connection is closed, the videogame frame because the player has changed area, or
the UI screen because a user interaction has changed the view.

So how can we manage all these objects and their required memory? The standard approach
of C programmers, and what it is still unfortunately taught in academia, is to use the
`malloc` and `free` APIs to allocate, and eventually release, these objects. This
requires the programmer to individually keep track of each object and remember when
their lifetime ends. This has created, over the years, the false belief that "*memory
management in C is hard to do and very error prone*". Well, if it's indeed done like
this, we cannot do anything but agree. Fortunately, this is not something intrinsically
tied to C itself, but rather to its misuse of the basic memory management APIs. C is a
simple language, and offers barebone constructs which you can use to build increasingly
complex applications. As much as no one would do logging by explicitly calling `fprintf`
every time, one must not treat memory with its primitive functions but rather create
something akin to a log library would do for logging: this is what the
`struct allocator` does.

For more information and in-depth study of C memory management we strongly encourage to
read [Ryan's article](https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator)
as we feel that none has done a better job than he to explain in great detail this topic.

The `struct allocator` follows the arena memory management approach: everything is
loaded on a specific allocator, which automatically grows the required memory in order
to satisfy the program needs. When the allocated objects are not needed anymore, a
single release call to the allocator is sufficient to release them all.

In order to use a `struct allocator`, it must be initialized to a given capacity with
the [allocator_init](#allocator-init) function. The returned object can then be passed
to the [allocator_push](#allocator-push) function to do the actual memory allocation.
This shall reserve some space in the allocator and consequently reduce the remaining
capacity. When a call to [allocator_push](#allocator-push) requires more memory than the
remaining capacity, then the allocator shall automatically extend it in order to
accomodate the request. The extension is transparent to the caller, and the allocator
guarantees that all returned pointers shall remain always valid.

When the user is done using the allocator, he may release all its memory at once by
calling the function [allocator_release](#allocator-release). After this call, all
objects, as well as their addresses -- that were stored in the allocator, are no longer
valid.

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

### buffer

TODO: describe the buffer.

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
