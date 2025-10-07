#include "set_each.h"

spec( set_each ) {
  precondition("a valid set");
    #define preconditions \
      set<int> set = set(int, { 3, 4, 5 });

  when("a custom index name is not given") {
    apply(preconditions);

    must("iterate over all elements of the set");
      int index = 0;
      for set_each(&set, int* element) {
        switch (index) {
        case 0:
          verify(*element == 3); break;
        case 1:
          verify(*element == 4); break;
        case 2:
          verify(*element == 5); break;
        }
        index++;
      }

    success();
  } end();

  when("a custom index name is given") {
    apply(preconditions);

    must("iterate over all elements of the set using the provided index name");
      int index = 0;
      for set_each(&set, int* element, custom_index) {
        switch (index) {
        case 0:
          verify(*element == 3); break;
        case 1:
          verify(*element == 4); break;
        case 2:
          verify(*element == 5); break;
        }

        verify(custom_index == index);
        index++;
      }

    success();
  } end();
}
