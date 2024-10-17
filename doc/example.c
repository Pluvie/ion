#include <src/ion.h>
#include <src/ion.c>

struct example {
  i32 number;
  u32 ages[4];
  struct array* values;
  struct {
    i32 value;
  } inner;
  struct pointed {
    i32 test;
    i32 abc;
  }* pointed;
};


struct new_reflect {
  char* name;
  u32 offset;
  u32 index;
  u32 bounds[2];
  enum types type;
  struct new_reflect* parent;
  struct vector* child;
  padding(16);
};
check_sizeof(struct new_reflect, 64);

#define new_type(type_name, ...) .type = type_name __VA_OPT__(, .bounds = { __VA_ARGS__ })
#define new_fields(...) .child = &vector_of(struct new_reflect, __VA_ARGS__)
#define new_field(struct_name, member_name) .offset = offsetof(struct_name, member_name), .name = #member_name
#define of(...) .child = &vector_of(struct new_reflect, { __VA_ARGS__ })

struct new_reflect example_schema = {
  new_type(STRUCT), new_fields({
    { new_field(struct example, number), new_type(I32) },
    { new_field(struct example, inner), new_type(STRUCT), new_fields({
      { new_field(struct example, inner.value), new_type(I32) } })
    },
    { new_field(struct example, ages), new_type(SEQUENCE, 4), of({ new_type(U32) }) },
    { new_field(struct example, values), new_type(ARRAY, 1, 3), of({
        new_type(ARRAY), of({ new_type(BYTE) })
      })
    },
    { new_field(struct example, pointed), new_type(POINTER), of({
        new_type(STRUCT), new_fields({
          { new_field(struct pointed, test), new_type(I32) },
          { new_field(struct pointed, abc), new_type(I32) },
        })
      })
    }
  })
};





void binary_encode (
    struct reflect* schema,
    struct protocol* binary
)
{
}




i32 main (
    i32 argc,
    char** argv
)
{
  struct memory allocator = memory_init(4096);

  struct request {
    bool boolean;
    i32 number;
  } request;

  struct reflect request_schema = {
    type(STRUCT, { sizeof(struct request), 2 }) {
      { field(boolean, struct request), type(BOOL) },
      { field(number, struct request), type(I32) },
    }
  };

  byte input_data[] = {
    /* boolean */   0x07,                       // 7 -> evaluates to `true`
    /* number */    0x04, 0x00, 0x00, 0x00,     // 4 little endian
  };
  struct io input = io_reader(input_data, sizeof(input_data));

  struct protocol binary = {
    .schema = &request_schema,
    .allocator = &allocator,
    .encode = binary_encode,
    .decode = binary_decode };
  decode(&binary, &input, &request, &(struct protocol_debug){ 0 });

  if (!binary.error.occurred) {
    fprintf(stderr, "\nDECODED REQUEST\n");
    fprintf(stderr, "boolean: %i\n", request.boolean);
    fprintf(stderr, "number: %i\n", request.number);
  }

  memory_release(&allocator);

  return EXIT_SUCCESS;
}

void complex_req () {
  struct memory allocator = memory_init(4096);

  struct request {
    bool sample;
    struct nested {
      bool nsample;
    } nested;
    struct ciccio {
      i64 from;
      bool active;
    } ciccio;
    i16 seq[2][2];
    struct array periods;
    struct array cicci;
    char* string;
    u64 test;
  } request;

  struct reflect ciccio_schema = {
    type(STRUCT, { sizeof(struct ciccio), 2 }) {
      { field(from, struct ciccio), type(I64) },
      { field(active, struct ciccio), type(BOOL) },
    }
  };

  struct reflect request_schema = {
    type(STRUCT, { sizeof(struct request), 8 }) {
      { field(sample, struct request), type(BOOL) },

      { field(nested, struct request), type(STRUCT, { sizeof(struct nested), 1 }) {
        { field(nsample, struct nested), type(BOOL) }
      } },

      { field(ciccio, struct request), schema(&ciccio_schema) },

      { field(seq, struct request), type(SEQUENCE, { 2 })
        {{ type(SEQUENCE, { 2 }) {{ type(I16) }} }}
      },

      { field(periods, struct request), type(ARRAY, { 0, 0 })
        {{ type(I8) }}
      },

      { field(cicci, struct request), type(ARRAY, { 0, 0 })
        {{ type(ARRAY, { 0, 0 })
          {{ schema(&ciccio_schema) }}
        }}
      },

      { field(string, struct request), type(POINTER, { 0 })
        {{ type(CHAR) }}
      },

      { field(test, struct request), type(U64) },
    }
  };

  byte input_data[] = {
    /* sample */                0x07,
    /* nested.nsample */        0x01,
    /* ciccio.from */           0x08, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 8 little endian
    /* ciccio.active */         0x01,
    /* seq */                   0x0a, 0x00, 0x09, 0x00,  0x0b, 0x00, 0x08, 0x00,  // [ [ 10, 9 ], [ 11, 8 ] ]
    /* periods.length */        0x03, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 3 little endian
    /* periods.data */          0x80, 0x01, 0xff,                                 // -128, 1, -1
    /* cicci.length */          0x02, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 2 little endian
    /* cicci.0.length */        0x02, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 2 little endian
    /* cicci.0.ciccio.from */   0x08, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 8 little endian
    /* cicci.0.ciccio.active */ 0x01,
    /* cicci.0.ciccio.from */   0x09, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 8 little endian
    /* cicci.0.ciccio.active */ 0x00,
    /* cicci.1.length */        0x01, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 2 little endian
    /* cicci.1.ciccio.from */   0xff, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 255 little endian
    /* cicci.1.ciccio.active */ 0x00,
    /* string.length */         0x08, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 8 little endian (strlen + nul byte)
    /* string.value */          0x70, 0x70, 0x70, 0x70,  0x70, 0x70, 0x70, 0x00,  // ppppppp
    /* test */                  0xff, 0x01, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  // 511 little endian
  };
  struct io input = io_reader(input_data, sizeof(input_data));

  struct protocol_debug debug;
  struct protocol binary = {
    .schema = &request_schema,
    .allocator = &allocator,
    .encode = binary_encode,
    .decode = binary_decode };
  decode(&binary, &input, &request, &debug);

  fprintf(stderr, "\nDECODED REQUEST\n");
  fprintf(stderr, "sample: %i\n", request.sample);
  fprintf(stderr, "nested.nsample: %i\n", request.nested.nsample);
  fprintf(stderr, "ciccio.from: %li\n", request.ciccio.from);
  fprintf(stderr, "ciccio.active: %i\n", request.ciccio.active);
  fprintf(stderr, "seq: [ [ %i, %i ], [ %i, %i ] ]\n",
    request.seq[0][0], request.seq[0][1],
    request.seq[1][0], request.seq[1][1]);
  fprintf(stderr, "periods: [ %i, %i, %i ]\n",
    as(i8, array_get(&(request.periods), 0)),
    as(i8, array_get(&(request.periods), 1)),
    as(i8, array_get(&(request.periods), 2)));
  fprintf(stderr, "cicci.length: %li\n", request.cicci.length);
  struct array cicci0 = as(struct array, array_get(&(request.cicci), 0));
  struct array cicci1 = as(struct array, array_get(&(request.cicci), 1));
  fprintf(stderr, "cicci.0.0.ciccio: [%li, %i]\n", as(struct ciccio, array_get(&cicci0, 0)).from, as(struct ciccio, array_get(&cicci0, 0)).active);
  fprintf(stderr, "cicci.1.0.ciccio: [%li, %i]\n", as(struct ciccio, array_get(&cicci1, 0)).from, as(struct ciccio, array_get(&cicci1, 0)).active);
  fprintf(stderr, "string: %s\n", request.string);
  fprintf(stderr, "test: %li\n", request.test);

  memory_release(&allocator);
}

void ttt () {
  struct player {
    char* name;
    u8 age;
  };

  struct tictactoe {
    u16 version;
    struct game {
      i8 field[3][3];
      struct player x;
      struct player o;
      i32 moves_count[2];
      bool wins_x;
      bool wins_o;
    } current;
    struct array daily_games;
  };
}
