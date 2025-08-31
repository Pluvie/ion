{
  if (io->rfx != NULL)
    goto decode;
  else
    goto discard;

decode:
  json_parse_spaces(io);
  json_decode_value(io, target);
  return;

discard:
  json_parse_spaces(io);
  json_discard_value(io);
  return;
}
