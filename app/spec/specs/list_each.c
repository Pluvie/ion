#include "list_each.h"

spec( list_each ) {

  precondition("a valid list");
    #define preconditions \
      list<int> list = list(int, { 3, 4, 5 });

  when("a custom index name is not given") {
    apply(preconditions);

    must("iterate over all elements of the list");
      int index = 0;
      for list_each(&list, int* element) {
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

    must("iterate over all elements of the list using the provided index name");
      int index = 0;
      for list_each(&list, int* element, custom_index) {
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
