<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Documentation

Landing page for all documented ⚡️ION⚡️ features and API.

## Features

- Type safe an fully qualified [Data Structures](#data-structures).
- [Reflection](#reflection) of any C program object.
- [Memory](#memory) management.
- Standardized primitive [Types](#types).

### Data Structures

With ⚡️ION⚡️ you can write this C code:

```c
struct rgb {
  int red;
  int green;
  int blue;
};

map<char*, struct rgb> colors = map(char*, struct rgb, {
  { "Violet", { 127, 0, 255 }   },
  { "Pink",   { 255, 192, 203 } },
  { "Lime",   { 32, 205, 32 }   };
});
```

And then operate on it using APIs like:

```c
map_get(&colors, "Pink");
// returns a (struct rgb*) to { 255, 192, 203 }

map_has(&colors, "Orange");
// returns false

map_set(&colors, "Orange", { 255, 165, 0 });
// adds the key/value to the map

map_has(&colors, "Orange");
// returns true
```

⚡️ION⚡️ comes with `list`, `set` and `map` prebuilt data structures, but also exposes
a mechanism that makes extremely trivial to implement any other data structure that you
need.

All data structures can hold *any* type, and are fully type safe: if you pass the wrong
type to any of the API the code won't compile.

To get started and know more about ⚡️ION⚡️ data structures refer to the [relative
documentation](data_structures.md).

### Reflection

TODO

### Memory

C is infamous for its difficulty in managing memory and providing a safe way to program
against it. While this is true to some extent, it has largely been exaggerated. Between
tools and programming practices, the memory problem *has been effectively solved* in C.
The only ones who still do not know it are people that are not involved into C
programming anymore and continue to spread misinformation.

It is of couse still possible to create a memory bug -- buffer overrun, stack overflow,
heap corruption, double free and the likes of it -- because it simply **is** allowed:
the inherent control that C gives to the programmers exposes them to this possibility.

But the mere existance of a possibility must not scare people away -- if the probability
of its occurence is low or can be lowered -- just as you still go outside every day even
though there is the chance of a meteor landing right on your head. As we said, tools and
programming practices have significantly reduced the memory bug probability to a value
close to 0, and you still retain the full control of the C language. To cite [Eskil
Steenberg](https://www.youtube.com/watch?v=443UNeGrFoM):

> At the beginning, all you want are results.
>
> In the end, all you want is control.

So what's the point of having a "safe" language (*cough* Rust *cough*) with an
**unsafe** keyword? It's like paying a whole year of subscription to the gym and go
there just once or twice. When you program with a "safe" language you pay this cost
every single line of code. Safety is not free. It's better to pay for its cost only when
it's actually needed. With C, tools like Valgrind or ASan can be run against automated
test suites or during handrolled checks, therefore reducing their cost by a significant
amount, and leaving the development phase clean and fluent.

Other than that, the best programming practice for avoiding a substantial amount of
memory related bugs is the use of allocators -- or also called arenas. It is not our
desire to explain this topic in detail here, since a [lot of information](
https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator) can be found on it
by simply searching online. The core concept behind allocators is that program objects
are best allocated and deallocated in bulk, rather than micromanaged using the `malloc`
/`free` interface. Identifying a program lifetime -- such as a web request, a videogame
frame, a UI screen -- and tying objects to that lifetime not only simplifies the
program code but also eliminates almost all memory related problems by simply reducing
the attack surface.

### Types

⚡️ION⚡️ wants to simplfy and bring some clarity to C primitive types. Long time C
programmers know that this is a very hard topic, so we offer a **very hot** take.
The only primitive types available when programming with ⚡️ION⚡️ library are:

```c
int
dec
str
bool
char
void
```

With both `int` and `char` that can be also `unsigned`.

**That's it! Quite a change right?**

The reasons behind this drastic approach are several. Let's talk about the `int` type.
⚡️ION⚡️ defines this type as:

> [...] the widest possible integer that can be operated with a single hardware
> instruction on the target architecture.
>
> [ion.h](../src/ion.h)

Historically, hardware evolution has changed CPU register widths (and even the amount
of bits in a byte!) to account for higher arithmetic capabilities. Therefore,
the C language has adapted by first introducing the `long` keyword, and then by
explicitly defining integer widths with like `int32_t`, `int64_t` and so on. Eventually,
the `intmax_t` type was introduced, with the idea of collecting the greatest int type
like ⚡️ION⚡️ does, but without enforcing the single instruction operation.

All these changes did not solve the problem, and nowadays we find ourselves in a real
int-type nightmare, with dozens of types, very little portability, and backwards
compatibility issues. This has happened in our opinion because the definition of these
types is coming from inside the language, therefore opening to wrong cases where an
`int64_t` might not even exist on the target architecture, or worse, when type
implementation changes [break the ABI](https://thephd.dev/intmax_t-hell-c++-c).

We instead posit that the language should be type-width agnostic, and only when
compiling a program for a specific architecture it must fix the width of its type to
that compilation target. This is done in ⚡️ION⚡️ by introducing the concept of
[PLATFORM](../src/ion/platform.h). It's not something entirely new, as software has
always been compiled for various architectures due to their different ISAs (x86, x64,
arm64, etc.). We just take this step a little further and add the `int` size into the
mix. This ensures:

  - **simplicity**: we just have one `int` type and the code adapts when compiled.
  - **portability**: for the same reason, the best portable code is code written once
    and compiled many times for different architectures, without intervention.
  - **efficiency**: `int` is operated in a single hardware instruction and therefore is
    the fastest type for the target architecture.

In summary we think that the solution to hardware changes *must not come from inside
the language*, but instead must be defined outside. Over time, ⚡️ION⚡️ wants to map
all relevant platforms as compilation targets, and define their widths and boundaries
once and for all. When new platforms will come -- like 128 and 256 bit architectures --
we will have to just define their platform header and make no changes to the code base.
This is much better than how it has been done until now, where would have had to
introduce `int128_t` and `int256_t` types that add even more confusion and reduce
portability.

#### Pointers and Main

Another benefit of having a sole `int` type regards pointers. One thing that has always
been of some concern to C developers is the fact that the size of an integer and the
size of a pointer *might* not be of the same value. This is of course bad because
pointer arithmetics are useful code practices.

That is why the `size_t`, `uintptr_t` and `ptrdiff_t` types [were introduced](
https://pvs-studio.com/en/blog/posts/cpp/a0050/), effectively solving the problem but
adding more confusion to the already plagued world of int types.

⚡️ION⚡️ guarantees that the `int` type is the greatest integer that can fit into a CPU
register and be operated with a single instruction. Therefore it follows that it is also
guaranteed that it has the exact same value of a pointer, since no hardware manufacturer
would ever produce a CPU that requires multiple instructions to dereference memory
pointers, as that would be a total loss of performance.

Finally, for all the good that ⚡️ION⚡️ `int` type does, there's one thing that even it
cannot do: the return type for the `main` function. The C standard mandates that the
return value of the `main` function must be `int`. Since ⚡️ION⚡️ redefines `int` as
`widest_int_t`, using it as type for `main` is feasible only on platforms where the
two types coincide (for example, 32-bit Windows). Therefore, ⚡️ION⚡️ exposes the `int0`
type, which translates directly to the native `int` type, and is then usable as return
type for the `main` function and all other cases where interoperability with the native
int type is needed.
