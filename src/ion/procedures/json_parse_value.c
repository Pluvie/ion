
  switch(*io_cursor(io)) {
  case '{':
    json_parse_object;
    break;

  case '[':
    json_parse_array;
    break;

  case '"':
    json_parse_string;
    break;

  case '-':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '9':
    json_parse_number;
    break;

  default:
    if (io_contains(io, "null", 4)) {
      json_parse_null;
      io_advance(io, 4);
      break;
    }

    if (io_contains(io, "true", 4)) {
      json_parse_true;
      io_advance(io, 4);
      break;
    }

    if (io_contains(io, "false", 5)) {
      json_parse_false;
      io_advance(io, 5);
      break;
    }

    if (io_exhausted(io))
      fail("unexpected end of io");
    else
      fail("unrecognized token");
  }
