void stream_init_defaults (
    void
)
{
  stdin.pointer = __stdin;
  stdout.pointer = __stdout;
  stderr.pointer = __stderr;
}
