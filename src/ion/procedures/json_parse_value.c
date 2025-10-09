
  switch(*json_cursor(source)) {
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
  case '8':
  case '9':
    json_parse_number;
    break;

  default:
    if (json_contains(source, "null", 4)) {
      json_parse_null;
      json_advance(source, 4);
      break;
    }

    if (json_contains(source, "true", 4)) {
      json_parse_true;
      json_advance(source, 4);
      break;
    }

    if (json_contains(source, "false", 5)) {
      json_parse_false;
      json_advance(source, 5);
      break;
    }

    if (json_exhausted(source))
      fail("unexpected end of io");
    else
      fail("unrecognized token");
  }
