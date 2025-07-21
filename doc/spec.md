<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Spec

⚡️ION⚡️ introduces a [framework](../src/spec/framework.h) to define function
specifications in a rigorous but also readable way.

A function spec enables the programmer to be more confident about its implementations,
and guarantees any function to:

- be well-defined on what is its expected input and output (*clarity*)
- leave no gray-areas or undefined behaviours (*completeness*)
- do exactly what it is supposed to do (*correctness*)

### Example

Suppose we have a function called `is_even()` which takes a number and returns `true`
if the number is even, and `false` otherwise.

With ⚡️ION⚡️, we can write a spec for this function in the following way:

```c
spec( is_even ) {

  argument(int number);

  when("the number is even") {
    number = 8;
    bool result = is_even(number);

    must("return true");
      verify(result == true);
  }

  or_when("the number is odd") {
    number = 7;
    bool result = is_even(number);

    must("return false");
      verify(result == false);
  }
}
```

This is of course a trivial example, but gives a good idea on how to utilize the spec
framework to define a function specification.

In addition, the specification itself is C code, which keeps the important info inside
the codebase. The developers and mantainers are thus less reliant on technical
documentation often found in a different setting.

### Use Case

A significant use case of the spec framework, which was indeed the spark for its birth,
is the [io_buffer_read](../src/ion/functions/io_buffer_read.c) function defined in the
⚡️ION⚡️ codebase.

This function works on a `struct io` object, which is a I/O abstraction over a specific
channel (memory, file, socket, pipe, and so on). There are cases when we want to
(or we must) read from an io channel without loading the entire channel data in memory:
imagine streaming a document, or scanning a huge file for text occurences, or parsing
any source which is not locally available.

In these cases, a buffered read may be the best approach: it keeps the memory footprint
low and allows us to maintain a lookahead/lookbehind window which is useful if we have
to move back and forth in a close interval, without incurring in double reads or, worse,
data loss.

The `io_buffer_read` function does exactly this: it must account for all edge cases
where we may be asking for data that exceeds the buffer, or when the channel returns
less data that what was expected (imagine partial info on a socket or pipe), while
managing the memory and the buffer cursor for us. All of this while maintaining a
"window" of data which is configurable in size. Below there is a visual example of a
buffered read of an IO:

<div align="center">
  <img src="io_buffer_read.gif" title="io_buffer_read"/>
</div>

In order to be extremely confident that our implementation satisfies these needs, we
decided to introduce the spec framework to:

- define exactly what these needs are (*clarity*)
- enumerate all possible scenarios (*completeness*)
- verify that all scenarios are handled as expected (*correctness*)

The resulting spec may be [viewed here](../src/spec/io_buffer_read.c).
