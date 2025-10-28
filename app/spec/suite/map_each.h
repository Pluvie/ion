#include "../spec.h"

cstr keys[8] = { 0 };
int values[8] = { 0 };
uint hashes[8] = { 0 };

int_t sort_by_position (
    const void* kpos1,
    const void* kpos2
)
{
  struct { cstr key; uint position; }* kp1 = (void*) kpos1;
  struct { cstr key; uint position; }* kp2 = (void*) kpos2;
  if (kp1->position > kp2->position) return 1;
  if (kp1->position < kp2->position) return -1;
  else return 0;
}
