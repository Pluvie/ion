<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Introduction

⚡️ION⚡️ is a library that aims to uplift and strenghten the C programming language.
Hence the name *Super C harge*.

It is designed to be a single header to be included directly in your source code. Due
to its innovative approach, its main audience are brand new projects or complete
refactors.

## Features

⚡️ION⚡️ shall provide efficient language constructs to:

  - offer fully type safe [data structures](doc/README.md#data-structures) like lists,
    maps and sets, which can hold any type.
  - enable the [reflection](doc/README.md#reflection) of any C program object.
  - introduce a [memory management](doc/README.md#memory) approach that can
    revolutionize the way C code is written.
  - [standardize data types](doc/README.md#types): integers, decimals, strings, etc.

See [here for a feature technical overview](doc/README.md) and [here for a
full API documentation](doc/API.md).

## Ecosystem

⚡️ION⚡️ comes with an ecosystem of libraries, which are built using its technology and
share its philosophy. This modular approach allows the user to hand pick the desired
functionalities. These libraries are:

  - [🗡️SER🛡️](https://github.com/Pluvie/ser): data serialization and deserialization.
  - 🌐NET📡: networking, ranging from low level TCP primitives to high level HTTP
    servers.
  - N💫VA: data persistance layer, for performance oriented coders.
  - *name to be defined*: textual and visual user interface.
  - *name to be defined*: 2D/3D graphics.

## Motivation

At the time of writing this (2025) the planet we are living on is facing some serious
challenges.

> Demand for energy is growing across many countries in the world, as people get richer
> and populations increase.
>
> If this increased demand is not offset by **improvements in energy efficiency
> elsewhere**, then our global energy consumption will continue to grow year-on-year.
> Growing energy consumption makes the challenge of transitioning our energy systems
> away from fossil fuels towards low-carbon sources of energy more difficult: new
> low-carbon energy has to meet this additional demand and try to displace existing
> fossil fuels in the energy mix.
>
> From [Energy Production and Consumption](
https://ourworldindata.org/energy-production-consumption) - OurWorldinData.org

All this is happening while the very air we have to breathe is getting more and more
polluted, plastic bottles are replacing fish in our oceans, and more than three billions
of people still live under the poverty line.

**Not a bright picture for our beloved Earth 🌍, isn't it?**

As bad as that sounds, talking about it isn't gonna change anything. The time to act is
now. But what can a single person, who is a software programmer for a living, can
do about this? Well, it turns out that researchers are showing that our computers are
consuming a *substantial chunk* of all that produced energy, and that is likely to
increase even more due to the [AI surge](
https://davidmytton.blog/how-much-energy-do-data-centers-use/).

We might not be able to do much about plastic or help reduce the poverty line, but *we
damn well can do something about that energy consumption* and all the pollution that
follows!

How? By producing better and more efficient software! Humanity's greatest challenge is
learning how to live on this planet without burning every resource completely and
annihilating every other organism and ecosystem. After all, we surely would not want
to discover that AI is going to give us [the Agent Smith's speech](
https://www.youtube.com/watch?v=YK7nwbtlQV8) in 50 years from now!

We already poured an enormous amount of energy and economy in developing a tech stack
around the C language. Instead of reinventing the wheel every time, we should capitalize
on this heritage and start focusing on the quality and efficiency of our products,
rather than reinventing new ways to package the exacts same products (plastics, anyone?).
Whether people realize it or not, C is going to stick with us for the foreseeable future.
And fortunately, that is a good thing! C, turns out, is an *extremely efficient*
language.

To give an example, a single add statement in Python, translates into roughly 100 CPU
instructions. In C, in translates to 1. Yes, just one! This is confirmed by our
[benchmarks](https://github.com/Pluvie/ser/blob/main/README.md#benchmarks) on parsing a
~100 MB JSON file. C takes about 170ms, where Python more than 2 seconds. That's a 12x
time improvement! Imagine that on your phone: a 12x improvement means that your battery
will last from a mere day to..  *more than 10 days!*.

This is why ⚡️ION⚡️ is born. We want to empower people to write efficient software by
democratizing C. We want to uplift program execution speed and quality. This is our
honest take in trying to improve this world a little bit.

## Contributing

Any contribution is very much welcome, especially regarding testing and code quality.
We did our best to write a full functional specification of ⚡️ION⚡️ APIs, but we are
aware that real world use cases are needed to baptize a software as production ready.

The only requirement to contributions is that they must adhere and maintain the existing
code style, purely for aesthetic purposes.
