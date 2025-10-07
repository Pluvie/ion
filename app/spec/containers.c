#include "spec.h"
#include "containers.h"

/*
  Lists.
*/

#define list_of int
#define list_cmp_function(v, u) v == u
#include <ion/containers/list.c>

#define list_of struct squadmate
#define list_cmp_function(v, u) string_equal(v.name, u.name)
#include <ion/containers/list.c>

/*
  Sets.
*/

#define set_of int
#define set_cmp_function(v, u) v == u
#define set_hash_function(v) v
#include <ion/containers/set.c>

#define set_of char*
#define set_cmp_function(v, u) streq(v, u)
#define set_hash_function(v) hash_djb2_str(v)
#include <ion/containers/set.c>

#define set_of struct squadmate
#define set_cmp_function(v, u) string_equal(v.name, u.name)
#define set_hash_function(v) hash_djb2(v.name.chars, v.name.length)
#include <ion/containers/set.c>
