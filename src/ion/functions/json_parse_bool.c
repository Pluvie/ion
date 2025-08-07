static inline int json_parse_bool (
    struct io* io
)
{
  slice peek = io_peek(io, 5);
  if (error.occurred)
    return -1;

  if (streq(s("true"), peek))
    return lengthof("true");

  if (streq(s("false"), peek))
    return lengthof("false"); 

  return -1;
}
