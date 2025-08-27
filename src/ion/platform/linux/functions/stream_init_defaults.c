void stream_init_defaults (
    void
)
{
  __stdin = (struct stream) { stdin, s("stdin"), "r" };
  __stdout = (struct stream) { stdout, s("stdout"), "w" };
  __stderr = (struct stream) { stderr, s("stderr"), "w" };
}
