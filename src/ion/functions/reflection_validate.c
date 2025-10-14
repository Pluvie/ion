void reflection_validate (
    void* target,
    struct reflection* reflection
)
{
  if (reflection->validator == nullptr)
    return;

  reflection->validator(target, reflection);
}
