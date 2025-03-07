#include "../../../../src/ion.h"
#include "../../../../src/ion.c"

void decode (
    void
)
{
  struct data {
    struct array* users;
  } data;

  struct user {
    char* name;
    u32 age;
    struct array* roles;
  };

  struct reflect data_reflection = {
    type(STRUCT, sizeof(struct data)), fields({
      { field(struct data, users), type(POINTER), of({
          type(ARRAY, 0, 0), of({
            type(STRUCT, sizeof(struct user)), fields({
              { field(struct user, name), type(POINTER), of({ type(CHAR) }) },
              { field(struct user, age), type(I32) },
              { field(struct user, roles), type(POINTER), of({
                  type(ARRAY, 0, 0), of({ type(POINTER), of({ type(CHAR) }) })
                })
              },
            })
          })
        })
      },
    })
  };

  struct memory allocator = memory_init(0);
  struct io json = file_read("decode.json", &allocator);
  struct object target = object(data, &data_reflection, &allocator);
  json_decode(&json, &target);

  struct user* user;

  user = array_get(data.users, 0);
  print("Done: { %s, %i, [ %s, %s ] }",
    user->name, user->age,
    *(char**) array_get(user->roles, 0),
    *(char**) array_get(user->roles, 1));

  user = array_get(data.users, 99999);
  print("Done: { %s, %i, [ %s, %s ] }",
    user->name, user->age,
    *(char**) array_get(user->roles, 0),
    *(char**) array_get(user->roles, 1));

  memory_release(&allocator);
}

i32 main (
    i32 argc,
    char** argv
)
{
  decode();
  return EXIT_SUCCESS;
}
