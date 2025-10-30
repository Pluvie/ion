#include "map_literal.h"

spec( map_literal ) {
  must("create a frozen stack allocated map of the given key/value pairs"); {
    str shep = str("Jane Shepard");
    str garrus = str("Garrus Vakarian");
    str liara = str("Liara T'Soni");
    struct squadmate values[] = {
      { str("Jane Shepard"),    SOLDIER,      800, 400 },
      { str("Garrus Vakarian"), INFILTRATOR,  600, 600 },
      { str("Liara T'Soni"),    ADEPT,        200, 800 },
    };
    cstr keys[] = { "shep", "garrus", "liara", };
    uint hashes[countof(keys)] = { 0 };
    struct squad_map squad = squad_map_literal(keys, values, hashes, countof(keys));

    verify(squad.keys.allocator == nullptr);
    verify(squad.keys.capacity == 3);
    verify(squad.keys.length == 3);
    verify(squad.length == 3);
    verify(str_equal(squad_map_get(&squad, "shep")->name, shep));
    verify(squad_map_get(&squad, "shep")->class == SOLDIER);
    verify(squad_map_get(&squad, "shep")->health == 800);
    verify(squad_map_get(&squad, "shep")->shields == 400);
    verify(str_equal(squad_map_get(&squad, "garrus")->name, garrus));
    verify(squad_map_get(&squad, "garrus")->class == INFILTRATOR);
    verify(squad_map_get(&squad, "garrus")->health == 600);
    verify(squad_map_get(&squad, "garrus")->shields == 600);
    verify(str_equal(squad_map_get(&squad, "liara")->name, liara));
    verify(squad_map_get(&squad, "liara")->class == ADEPT);
    verify(squad_map_get(&squad, "liara")->health == 200);
    verify(squad_map_get(&squad, "liara")->shields == 800);

  } success();
}
