str str_strip (
    str source
)
{
  str stripped = { 0 };
  uint position_ahead;
  uint position_behind;

  if (source.length == 0)
    return stripped;

  position_ahead = 0;
strip_ahead:
  switch (source.chars[position_ahead]) {
  case ' ':
  case '\t':
  case '\n':
  case '\r':
  case '\f':
  case '\v':
    position_ahead++;
    if (position_ahead >= source.length)
      return stripped;

    goto strip_ahead;
  }

  position_behind = source.length - 1;
strip_behind:
  switch (source.chars[position_behind]) {
  case ' ':
  case '\t':
  case '\n':
  case '\r':
  case '\f':
  case '\v':
    if (position_behind == position_ahead)
      break;

    position_behind--;
    goto strip_behind;
  }

  stripped.chars = source.chars + position_ahead;
  stripped.length = position_behind - position_ahead + 1;
  return stripped;
}
