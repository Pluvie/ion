# Before running this file, compile the `python__bindings.c` file with this command:
#
# ```shell
# bin/compile python__bindings -o exe/python__bindings.so -shared -fPIC
# ```
#
# This shall create an `exe/python__bindings.so` file, which shall be used by the
# Python ctypes module to interoperate with the ⚡️ION⚡️ library.

import ctypes

_ion = ctypes.CDLL('exe/python__bindings.so')
_ion.example_sum.argtypes = (ctypes.c_int, ctypes.POINTER(ctypes.c_int))

def example_sum(numbers):
  global _ion
  numbers_length = len(numbers)
  array_type = ctypes.c_int * numbers_length
  result = _ion.example_sum(ctypes.c_int(numbers_length), array_type(*numbers))
  return int(result)

numbers = [ 1, 2, 3, 4 ]
print("The example sum of numbers is: ", example_sum(numbers))
