<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Introduction

⚡️ION⚡️ is a C substratum that aims to provide many useful features through *syntax
elegance* and *semantic cohesion*.

It is designed to be a single library to be included directly in your source code or
to be linked in dynamic loading. It shall provide efficient language constructs to:

  - offer ready to use data structures like [lists](#list), [maps](#map) and
    [sets](#set) which can hold any type.
  - [serialize](#serialization) to / from many data formats like JSON, XML, CSV,
    etc. and provide an easy way to create your serialization in any other new format.
  - enable the introspection of any C language struct through [reflection](#reflection).
  - introduce a [memory management](#memory) approach that can revolutionize
    the way C code is written.

and many other minor improvements like:

  - normalize [io operations](#io) on files, sockets, and memory objects.
  - [standardize data types](#types): integers, decimals, strings, etc.

## Features

A brief overview of ⚡️ION⚡️ features. To know more, read the full [documentation](
doc/README.md).

### List

```c
list<char*> fruits = list(char*, { "Apple", "Banana", "Cherry" });
print(fruits.length); // 3

char* fruit = list_pop(&fruits);
print(fruit);         // "Cherry"
print(fruits.length); // 2

list_push("Orange");
print(fruits.length); // 3
```

### Map

```c
map<char*, struct rgb> colors = map_init(char*, struct rgb, 8);

map_set(&colors, "Violet", { 127, 0, 255 });
map_set(&colors, "Pink", { 255, 192, 203 });

print(colors.length); // 2
struct rgb violet = map_get(&colors, "Violet");
print(violet);        // { 127, 0, 255 }

bool has_lime = map_has(&colors, "Lime");
print(has_lime);      // false
map_set(&colors, "Lime", { 32, 205, 32 });
print(colors.length); // 3
has_lime = map_has(&colors, "Lime");
print(has_lime);      // true
```

### Set

```c
set<char*> names = set_init(char*, 8);

set_add(&names, "Alpha");
set_add(&names, "Bravo");
set_add(&names, "Charlie");
print(names.length);  // 3

set_add(&names, "Alpha");
print(names.length);  // 3, no duplicates!

set_del(&names, "Bravo");
print(names.length);  // 2
```

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
