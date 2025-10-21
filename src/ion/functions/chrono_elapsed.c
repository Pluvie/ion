int chrono_elapsed (
    struct chrono* c
)
{
  return c->stop - c->start;
}
