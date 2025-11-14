<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## API

Allocator

  - [allocator_init](#allocator-init)
  - [allocator_pop](#allocator-pop)
  - [allocator_push](#allocator-push)
  - [allocator_release](#allocator-release)

Buffer

  - [buffer_address](#buffer-address)
  - [buffer_address_at](#buffer-address-at)

### allocator init

```c
struct allocator allocator_init (
    uint capacity
);
```

#### Description

This function initializes a `struct allocator` with the given *capacity*.

A `struct allocator` is a memory allocator and tracker. It is used to group code objects
that share the same lifetime across the program. Imagine a web request, a videogame
frame or a UI screen: all these entities require many objects to be readily accessible
from memory in order for the program to work correctly. But these same objects may well
not be required anymore when the entity has done its job: in case of the the web request
because it is completed and the connection is closed, the videogame frame because the
player has changed area, or the UI screen because a user interaction has changed the
view.

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

A pointer to the available space in the buffer memory after an amount of bytes equal
to *position*.

#### Errors

This function never fails. If the *position* is greater than the buffer current
position, this function shall [abort](
https://www.man7.org/linux/man-pages/man3/abort.3.html).
