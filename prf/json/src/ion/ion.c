#include "../../../../src/ion.h"
#include "../../../../src/ion.c"

void decode (
    void
)
{
  struct {
    struct array* users;
  } data;

  struct user {
    struct string name;
    u32 age;
    struct array* roles;
  };

  struct reflection data_rfx = {
    type(STRUCT, typeof(data)), fields({
      { field(users, POINTER, typeof(data)), of({
          type(ARRAY), of({
            type(STRUCT, struct user), fields({
              { field(name, STRING, struct user) },
              { field(age, I32, struct user) },
              { field(roles, POINTER, struct user), of({
                  type(ARRAY), of({ type(STRING) })
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
  if (error.occurred) {
    error_print();
    return;
  }

  reflection_initialize(&data_rfx, &data, &allocator);
  json_decode(&json, &data_rfx);

  struct user* user;

  user = array_get(data.users, 0);
  print("Done: { %.*s, %i, [ %.*s, %.*s ] }",
    sp(&(user->name)), user->age,
    sp((struct string*) array_get(user->roles, 0)),
    sp((struct string*) array_get(user->roles, 1)));

  user = array_get(data.users, 99999);
  print("Done: { %.*s, %i, [ %.*s, %.*s ] }",
    sp(&(user->name)), user->age,
    sp((struct string*) array_get(user->roles, 0)),
    sp((struct string*) array_get(user->roles, 1)));

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
