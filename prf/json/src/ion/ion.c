#include "../src/ion.h"
#include "../src/ion.c"

struct user {
  string name;
  int age;
  list<string> roles;
};

#define list_of struct user
#include "ion/types/list.h"

#undef list_function
#define list_function(s, f, ...)                  \
  _Generic(*(s),                                  \
    list<struct user> : list<struct user>_ ## f,  \
    _list_function(v, f, __VA_ARGS__)             \
  )

void decode (
    void
)
{
  //struct {
  //  list<struct user>* users;
  //} data;


  //struct reflection data_rfx = {
  //  type(STRUCT, typeof(data)), fields({
  //    { field(users, POINTER, typeof(data)), of({
  //        type(LIST), container(list<struct user>_), of({
  //          type(STRUCT, struct user), fields({
  //            { field(name, STRING, struct user) },
  //            { field(age, INT, struct user) },
  //            { field(roles, LIST, struct user),
  //                container(list<string>_),
  //                of({ type(STRING) })
  //            },
  //          })
  //        })
  //      })
  //    },
  //  })
  //};

  struct memory allocator = memory_init(0);
  struct file file = file_open(s("exe/decode.json"));
  int size = file_size(&file);
  void* content = memory_alloc(&allocator, size);
  file_read(&file, content, size);

  struct io json = io(content, size);
  //json_decode(&data, &json, &data_rfx, &allocator);
  //json_decode(NULL, &json, NULL, NULL);
  json_decode_direct(&json);

  //struct user* user;

  //user = list_at(data.users, 0);
  //print("Done: { %.*s, %li, [ %.*s, %.*s ] }",
  //  sp(user->name), user->age,
  //  sp(*list_at(&user->roles, 0)),
  //  sp(*list_at(&user->roles, 1)));

  //user = list_at(data.users, 9999999);
  //print("Done: { %.*s, %li, [ %.*s, %.*s ] }",
  //  sp(user->name), user->age,
  //  sp(*list_at(&user->roles, 0)),
  //  sp(*list_at(&user->roles, 1)));

  //user = list_at(data.users, 10000000);
  //print("Done: { %.*s, %li, [ %.*s, %.*s ] }",
  //  sp(user->name), user->age,
  //  sp(*list_at(&user->roles, 0)),
  //  sp(*list_at(&user->roles, 1)));

  memory_release(&allocator);
}

int32 main (
    int32 argc,
    char** argv
)
{
  decode();
  return EXIT_SUCCESS;
}
