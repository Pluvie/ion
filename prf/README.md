<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Performance

The `prf` directory is used to host a series of performance tests agains other famous
(or not so famous) implementations of __Ion__ features.

### Map

The map data structure is benchmarked against:

  - [absl::flat_hash_map](https://abseil.io/docs/cpp/guides/container) from Google's Abseil library.
  - [ska::flat_hash_map](https://doc.rust-lang.org/std/collections/struct.HashMap.html) from Malte Skarupke.
  - [map](https://go.dev/blog/maps) from Go programming language.
  - [HashMap](https://doc.rust-lang.org/std/collections/struct.HashMap.html) from Rust programming language.

### JSON

The JSON decoding capability is benchmarked against:

  - [encoding/json](https://pkg.go.dev/encoding/json) from Go programming language.
