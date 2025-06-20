##
# This simple Python script is all the C preprocessor needs right now:
#
# !!! A FREAKING NAME MANGLER !!!
#
# Yeah, with just this little functionality a world of possibilities opens before
# our heart-shaped developer eyes.
#
# This script basically reads a post-processed C source (i.e. with all macros expanded)
# and substitutes each occurrence of tokens like `map<int, string>` with the appropriate
# mangled name.
#
# This allows us to build type containers in pure C, and with the introduction of C11
# `_Generic` expression, a wealth of unprecedented possibilities are now open for the
# die hard C developers.

import sys
import re


# `s` is a type container like: `map<int, struct user*>`
def mangle(s):
  # `_sym` becomes `map`
  # `_type` contains `<int, struct user*>`
  _sym = s[:s.find("<")]
  _type = s[s.find("<"):]

  # We may now apply the appropriate substitutions in order to mangle the type.
  return (_sym + "_" + _type.
      replace(",", "__").
      replace("struct ", "struct_").
      replace(" ", "").
      replace("*", "_p").
      replace("[", "").
      replace("]", "").
      replace("(", "").
      replace(")", "").
      replace("<", "").
      replace(">", ""))


# Prints to `stdout` the full content of the file, received from `stdin`.
pattern = re.compile(r'([a-z_]+<[a-z0-9_,\*\[\]\(\) ]+>)')
content = sys.stdin.read()
# Increment the range depending on how many nested data structures you have.
for i in range(2):
  content = re.sub(pattern, lambda m: mangle(m.group()), content)
print(content, end="")
