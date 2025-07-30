<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Types

⚡️ION⚡️ aims to standardize the way C code is written by setting a convention on types.
The base types that are available are:

  - `int` a 64bit signed integer.
  - `dec` a 64bit double precision decimal.
  - `bool` a 32bit boolean value.
  - `char` a 8bit signed integer representing ASCII characters.
  - `void` a type obfuscator.
  - `string` a 128bit string of characters with incorporated length.
  - `memory` a 512bit memory allocator.

Type attributes like `long` and `unsigned` are gone: the idea is to reduce the
alternatives without restricting freedom, by standing on the mantra:

> Few choices, full control.

This is justified by the fact that having many integer or decimal types in modern
programming landscape is not helpful -- embedded systems being a different world,
which is not the one ⚡️ION⚡️ is aiming for.

Also, unsigned integers, while being a nice concept, are a common source of programming
errors, due to the fact that negative values are interpreted as positive: e.g. a 16bit
unsigned integer written in code as `-1` is actually `65535` for the CPU register.
By always using signed integers, the program is less prone to confusion, and at the same
time everything that was possible before, it still is now, without limiting the freedom
of the developer.

Additionally, as you can see by having `memory` in the base types list, ⚡️ION⚡️ treats
memory in a completely different way of what you may be used to see in C programs.
The main idea is to completely avoid memory (anti-)patterns like `malloc` / `free`,
object constructors / destructors, garbage collectors and borrowing models. One of
the main advantages of C is manual memory management: when done right, this can
translate in a fine grained control over your program resource usage. The problem is,
it almost has never been done right. That is way so many programming languages have
been given birth, 99% of whom with the motivation of "memory safety". One can judge if
this endeavor has been worth the trouble. ⚡️ION⚡️, instead, does not want to add (yet)
another programming language, but instead introduces a new approach, which can hopefully
bring peace over this debate: more details on the [specific chapter](doc/memory.md).
