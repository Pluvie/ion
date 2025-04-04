struct ring;
/**
 * The `struct ring` is a circular memory abstraction to simplify allocation and
 * deallocation of many objects, especially when the memory need to be reused
 * without fragmentation.
 *
 * Contrary to the other allocators, a ring supports removal of specific segments of
 * data from its memory, whereas `struct memory` and `struct buffer` allocator can
 * remove data only all at once -- when they release their content.
 *
 * When removing data from the ring, this is done from the beginnig: this frees up
 * space for new future data. Adding data to the ring is done from the end, and when
 * the ring reaches its capacity, it shall start to add from the beginning again. */
struct ring {
  u64 capacity;
  u64 allocated_space;
  u64 free_space;
  u64 begin;
  u64 end;
  byte* data;
  byte* junction;
  padding(8);
};
check_sizeof(struct ring, 64);
