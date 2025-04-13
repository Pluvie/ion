static inline bool set_comparer(t) (
    t* e1,
    t* e2
)
{
  return memeq(e1, e2, sizeof(t));
}
