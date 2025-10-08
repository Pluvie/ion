#if standard(>= C11)
  #define json_decode(input, reflection, target)  \
    _Generic(input,                               \
      char* : json_decode_direct,                 \
    )(input, reflection, target)
#endif
