#include "functions/set_add.c"
#include "functions/set_init.c"

struct N container_function(N, alloc) (
    uint initial_capacity,
    struct allocator* allocator
)
{
  struct N set = { 0 };
  uint capacity = initial_capacity;

  if (initial_capacity < 16)
    capacity = 16;
  else
    capacity = next_pow2(initial_capacity);

  set.capacity = capacity;
  set.allocator = allocator;
  set.data = allocator_push(allocator, capacity * sizeof(T));
  set.hashes = allocator_push(allocator, capacity * sizeof(uint));
  set.load_limit = set_load_limit(&set);

  memory_set(set.data, 0, capacity * sizeof(T));
  memory_set(set.hashes, 0, capacity * sizeof(uint));

  return set;
}

uint container_function(N, del) (
    struct N* set,
    T element
)
{
  uint position = container_function(N, pos)(set, element);
  if (position == set_pos_invalid)
    return set_pos_invalid;

  if (set_pos_is_free(set, position))
    return set_pos_invalid;

  set_pos_free(set, position);
  set->length--;
  return position;
}

/*
bool container_function(N, each) (
    N* set,
    struct iterator* iter
)
{
  iter->gate = ~0;

  for (; iter->position < set->capacity; iter->position++)
    if (set_pos_is_occupied(set, iter->position))
      return true;

  return false;
}
*/

bool container_function(N, has) (
    struct N* set,
    T element
)
{
  uint position = container_function(N, pos)(set, element);
  if (position == set_pos_invalid)
    return false;

  return set_pos_is_occupied(set, position);
}

/*
N container_function(N, literal) (
    uint capacity,
    T* data,
    uint* empty_hashes
)
{
  N set = {
    .data = data,
    .hashes = empty_hashes,
    .capacity = capacity,
    .load_limit = capacity,
    .length = capacity,
  };

  for (int i = 0; i < capacity; i++)
    set_pos_occupy(&set, i, container_hasher(data[i]));

  return set;
}
*/

uint container_function(N, pos) (
    struct N* set,
    T element
)
{
  T* probed_element;

  uint element_hash = container_hasher(element); 
  uint probe_index = element_hash & (set->capacity - 1);
  uint probe_index_limit = set->capacity - 1;
  uint initial_probe_index = probe_index;

linear_probing:
  probed_element = set->data + probe_index;

  if (set_pos_is_free(set, probe_index))
    return probe_index;

  if (container_equalizer(element, (*probed_element)))
    return probe_index;

  probe_index++;
  if (probe_index > probe_index_limit)
    probe_index = 0;

  if (probe_index != initial_probe_index)
    goto linear_probing;

  return set_pos_invalid;
}

void container_function(N, rehash) (
    struct N* set
)
{
  struct N rehashed_set = { 0 };
  T* element; uint element_index;
  uint new_capacity = set->capacity * 2;

  rehashed_set.capacity = new_capacity;
  rehashed_set.data = allocator_push(set->allocator, new_capacity * sizeof(T));
  rehashed_set.hashes = allocator_push(set->allocator, new_capacity * sizeof(uint));
  rehashed_set.load_limit = set_load_limit(&rehashed_set);

  memory_set(rehashed_set.data, 0, new_capacity * sizeof(T));
  memory_set(rehashed_set.hashes, 0, new_capacity * sizeof(uint));

  for (element_index = 0; element_index < set->capacity; element_index++) {
    if (set_pos_is_free(set, element_index))
      continue;

    element = set->data + element_index;
    container_function(N, add)(&rehashed_set, *element);
  }

  set->capacity = new_capacity;
  set->data = rehashed_set.data;
  set->hashes = rehashed_set.hashes;
  set->load_limit = set_load_limit(&rehashed_set);
}
