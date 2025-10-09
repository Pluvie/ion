void reflection_validate (
    void* target,
    struct reflection* reflection
)
{
  if (reflection->validator == nullptr)
    return;

  if (reflection->validator(target, reflection))
    return;
}
