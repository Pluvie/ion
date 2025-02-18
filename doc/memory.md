<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Memory (.. and its management)

The C programming language has been living for some time with the stigma of a "keep
out of children reach", mainly due to its need to manually manage the program memory.

In the early days, it was not so. Then, during the following years, a plethora of
programming languages were born that miracolously saved the programmer from the burden
of *manual memory management*, claiming security and stability for all. Granted,
software security and stability was not so important in the 1980s as it is now, but
nonetheless there still are, in this very moment, a lot of programs written in C
that keep the world running -- literally.

So, what's the deal? is C really something only for the top skilled programmers, while
the others have to stick with Go, Python and Rust for all their existance?

Well, the answer, of course, is no. C is for everyone. But you have to use the right
tool for the job.

### Malloc et al.

If you have to cut down a hundreds of years old tree, would you rather use a billhook or
a chainsaw? You would no doubt use a chainsaw: more speed, less fatigue, and you get
the job done. It's a win-win.

So, why when you need to allocate memory for a program you use the `malloc` function
for *every single* object in your source code? Is this granular control really needed?
In almost all circumstances, it is not. Instead, it is way easier to tie an object
lifetime to a program state, rather than keep track of the referencing objects with a
complex data structure like most garbage collectors do.

We shall not indulge on this topic long, since an illuminating read on the topic can be
[already found here](https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator).
Suffice to say, memory management is better -- and more easily done -- in bulk, rather
than individually: the core idea is to use an __allocator__ for all lifetimes needed
for a specific program state (i.e. an ui screen, a web request, a videogame frame)
and then, when the state ends, releasing all memory at once.

### Memory and Buffer

⚡️ION⚡️ thrives on this concept offering two structs:

```c
struct memory;
struct buffer;
```

to allocate / release bulks of objects. The main difference between the two is the
memory layout and pointer validity.

#### Memory

A `struct memory` exposes the following interface:

```c
struct memory memory_init(u64 initial_capacity);
void* memory_alloc(struct memory* allocator, u64 amount);
void* memory_alloc_zero(struct memory* allocator, u64 amount);
void memory_release(struct memory* allocator);
```
