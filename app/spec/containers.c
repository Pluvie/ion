#include "spec.h"
#include "containers.h"

/*
  Lists.
*/

#define list_of int
#define list_cmp_function(v, u) v == u
#include <ion/containers/list.c>

#define list_of struct squadmate
#define list_cmp_function(v, u) str_equal(v.name, u.name)
#include <ion/containers/list.c>

/*
  Sets.
*/

#define set_of int
#define set_cmp_function(v, u) v == u
#define set_hash_function(v) v
#include <ion/containers/set.c>

#define set_of char*
#define set_cmp_function(v, u) cstr_equal(v, u)
#define set_hash_function(v) hash_djb2_cstr(v)
#include <ion/containers/set.c>

#define set_of str
#define set_cmp_function(v, u) str_equal(v, u)
#define set_hash_function(v) hash_djb2(v.chars, v.length)
#include <ion/containers/set.c>

#define set_of struct squadmate
#define set_cmp_function(v, u) str_equal(v.name, u.name)
#define set_hash_function(v) hash_djb2(v.name.chars, v.name.length)
#include <ion/containers/set.c>

/*
  Maps.
*/

#define map_of char*, int
#define map_cmp_function(v, u) cstr_equal(v, u)
#define map_hash_function(v) hash_djb2_cstr(v)
#include <ion/containers/map.c>

#define map_of char*, struct squadmate
#define map_cmp_function(v, u) cstr_equal(v, u)
#define map_hash_function(v) hash_djb2_cstr(v)
#include <ion/containers/map.c>

#define map_of str, struct squadmate
#define map_cmp_function(v, u) str_equal(v, u)
#define map_hash_function(v) hash_djb2(v.chars, v.length)
#include <ion/containers/map.c>
