bool is_adult (
    void* age_ptr,
    struct reflection* rfx
)
{
  u16 age = *(u16*) age_ptr;
  if (age >= 18)
    return true;

  fail("must be greater or equal than 18");
  return false;
}



bool all_numbers_greater_than_zero (
    void* numbers_ptr,
    struct reflection* rfx
)
{
  struct array* numbers = (struct array*) numbers_ptr;
  for array_each(numbers, i32*, number)
    if (*number <= 0) {
      fail("all numbers must be greater than 0");
      return false;
    }

  return true;
}
