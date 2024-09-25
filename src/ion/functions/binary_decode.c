void binary_decode (
    struct protocol* decoder
)
{
  switch (decoder->schema->type) {
  case U8:
  case U16:
  case U32:
  case U64:
  case I8:
  case I16:
  case I32:
  case I64:
  case D32:
  case D64:
  case D128:
  case BYTE:
  case CHAR:
  case BOOL:
    call(binary_decode_primitive, decoder);
    break;

  case STRUCT:
    call(binary_decode_struct, decoder);
    break;

  case ARRAY:
    call(binary_decode_array, decoder);
    break;

  case POINTER:
    call(binary_decode_pointer, decoder);
    break;

  case SEQUENCE:
    call(binary_decode_sequence, decoder);
    break;
  }
}
