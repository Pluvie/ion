<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Documentation

Landing page for all documented ⚡️ION⚡️ features.

- [Spec system](spec.md)
- More to come

### Things that need more documentation

- A feature of `json_decode_string` which, if the io channel is memory, and it is not
  buffered, it does not use the allocator to make a copy of the string, but instead
  points to the io memory area directly.

- More spec cases for `io_error_extract` and `reflection_error_extract`: they should
  cover many more edge cases.
