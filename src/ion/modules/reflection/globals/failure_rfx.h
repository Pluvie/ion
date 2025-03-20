struct reflection failure_rfx = {

  #define failure_t   struct failure
  #define trace_t     typeof(*o(struct failure)->trace)

  type(STRUCT, failure_t), fields({
    { field(occurred,     BOOL,     failure_t) },
    { field(length,       U32,      failure_t) },
    { field(trace_count,  U32,      failure_t) },
    { field(trace,        SEQUENCE, failure_t), of({
        type(STRUCT, trace_t), fields({
          { field(file, POINTER,  trace_t), of({ type(CHAR) }) },
          { field(line, U64,      trace_t) },
        })
      })
    },
    { field(message,      SEQUENCE, failure_t), of({ type(CHAR) }) },
  })

  #undef failure_t
  #undef trace_t
};
