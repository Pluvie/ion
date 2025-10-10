

## Compatibility

⚡️ION⚡️ minimum standard requirement is C99, but newer standards are supported as well.
We suggest targeting for C11 or higher standard, mainly because this enables a more
convenient way to use data structures through the use of the `_Generic` construct.

C89 standard (or ANSI C) is not supported. Even though
[Eskil Steenberg](https://www.quelsolaar.com/about/index.html) -- who I personally
admire and hold in high esteem -- is correctly advising C89 as the most dependable
language, he is still using a subset of C99 due to important funcionalities like
`snprintf` which are not part of ANSI C.

## Motivation

C is [old](https://dl.acm.org/doi/10.1145/155360.155580). Probably older than most of
us reading this text. It has resisted the trial of time, and still runs under the vast
majority of our machines.

And rightfully so. Its concept and design are pristine and simple. Its speed, unmatched.
⚡️ION⚡️ wants to capitalize upon this heritage, by giving tools that can can extend its
usage in the current programming landscape.

We believe that the status of the modern software ecosystem is bad. Programs are slow
and expensive. This is, in our opinion, due to two main reasons:

  1. the programming language landscape is all about abstraction and object-oriented
     approach, but this has [little to do](https://caseymuratori.com/blog_0015) with
     the real computer world and leads to..
  2. programmers not becoming aware of how the underlying hardware works and thus
     are unable to optimize for performance.

We hope to show that achieving code clarity and efficiency is not only still possible,
but it has been so since the early days. Only by choosing the wrong evolution path did
we reach this stagnation point. We need to return to our roots and build again from
there: this is why ⚡️ION⚡️ is born.

## Data Structures

A big part of computer science theory revolves around algorithms and data structures.
They have been extensively used to [solve real-world problems](
https://en.wikipedia.org/wiki/Seven_Bridges_of_K%C3%B6nigsberg) in the most efficient
way possible.

However, back in the 1970s, when C was born, computers were not as widespread as they
are now, and a lot of research had yet to be done. Over the following years, it became
more and more evident how we could rapidly solve complex computational problems by
simply implementing the correct -- and mathematically already well-defined -- algorithm
and/or data structure.

This is why C lags behind in this compartment compared to newer languages. It is not
the fact that it's not possible to *implement* these things in C -- it is of course
[Turing Complete](https://en.wikipedia.org/wiki/Turing_completeness) -- but rather the
fact that it does not expose a syntactical and type-safe way to do so.

We posit that all that is required to achieve this is a __symbol inflection__ directly
[integrated in the preprocessor](bin/ion.py). Using ⚡️ION⚡️, it is possible to do things
like:

```c
list<char*> fruits = list(char*, { "Apple", "Banana", "Cherry" });

list_at(&fruits, 1);  // "Banana"
list_pop(&fruits);    // Returns an always valid reference to "Cherry"
list_push(&fruits, "Orange");
```

⚡️ION⚡️ data structures work with any type. Suppose a:

```c
struct rgb {
  int red;
  int green;
  int blue;
};
```

It is possible to do:

```c
map<char*, struct rgb> colors = map(char*, struct rgb, {
  { "Violet", { 127, 0, 255 } },
  { "Pink", { 255, 192, 203 } },
  { "Lime", { 32, 205, 32 } };
});

map_get(&colors, "Pink");     // { 255, 192, 203 }
map_has(&colors, "Orange");   // false
map_set(&colors, "Orange", { 255, 165, 0 });
map_has(&colors, "Orange");   // true
```

## Serialization

Converting to and from various data formats has become a very important task that
programmers must do in order to integrate their software with others. ⚡️ION⚡️ ships
with ready to use conversion in JSON, CSV, XML and gRPC formats, in order to accomodate
the most real world scenarios possible.

If the format you need is not one of those, do not worry: the good thing is that,
through ⚡️ION⚡️ [reflection](#reflection) you can implement it so easily like has never
seen before in C language.

Let's see a JSON example:

```json
{
  "title": "Landline Positions",
  "names": [ "Alpha", "Bravo", "Charlie" ],
  "positions": {
    "Alpha": [ 12.0, 12.0 ],
    "Bravo": [ -12.0, 8.0 ],
    "Charlie": [ -8.0, -8.0 ]
  },
}
```

```c
char* json = ... // See above

struct data {
  set<string> names;
  map<string, int[2]> positions;
  int last_update;
};

// Here we define the reflection that we want to apply to this struct.
struct reflection rfx = {
  type(STRUCT, struct data), fields({
    // We are not interested in the "title" field, so we just omit it!.

    { field(names, SET, struct data), of({ type(STRING) }) },
    // The "names" field is a JSON array, but we want a set to ensure that there
    // are no duplicates.

    { field(positions, MAP, struct data), of({ type(STRING),
        of({ type(ARRAY, int[2]), of({ type(INT) }) })
      })
    },
    // The "positions" field is a dynamic map with strings and a pair of coordinates.
    // We could have used the `list<int>` type, but instead we use an array `int[2]`
    // to clarify that we expect only 2 values.

    { field(last_update, INT, struct data) },
    // This field is missing in the JSON, but no worries: it shall be initialized to 0.
  })
};

json_decode(json, &data, &rfx, allocator);
print(data.names);        // [ "Alpha", "Bravo", "Charlie" ]
print(data.positions);    // { "Alpha": [ 12.0, 12.0 ], ... }
print(data.last_update);  // 0, field was missing.
```
