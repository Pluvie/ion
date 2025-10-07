//#include <ion.h>
//
//#define list_of struct squadmate
//#include <ion/containers/list.h>
//
//int0 main (
//    int0 argc,
//    char** argv
//)
//{
//  list<struct squadmate> list = { 0 };
//  printf(">>>>> %p", list.data);
//  return 0;
//}

enum classes {
  SOLDIER,
  VANGUARD,
  INFILTRATOR,
  ENGINEER,
  SENTINEL,
  ADEPT,
};

struct squadmate {
  char* name;
  enum classes class;
  unsigned int health;
  unsigned int shields;
};

void map_literal (
    unsigned int capacity,
    char** keys,
    struct squadmate* values,
    unsigned int* hashes,
    void* pairs
) { }

int main(int argc, char** argv) {

map_literal( (sizeof((struct { char* k; struct squadmate v; } []) { { "Jane Shepard", { .class = SOLDIER, .health = 800, .shields = 400 } }, { "Garrus Vakarian", { .class = INFILTRATOR, .health = 600, .shields = 600 } }, { "Liara T'Soni", { .class = ADEPT, .health = 200, .shields = 800 } }, }) / sizeof(*((struct { char* k; struct squadmate v; } []) { { "Jane Shepard", { .class = SOLDIER, .health = 800, .shields = 400 } }, { "Garrus Vakarian", { .class = INFILTRATOR, .health = 600, .shields = 600 } }, { "Liara T'Soni", { .class = ADEPT, .health = 200, .shields = 800 } }, }))), (char* [(sizeof((struct { char* k; struct squadmate v; } []) { { "Jane Shepard", { .class = SOLDIER, .health = 800, .shields = 400 } }, { "Garrus Vakarian", { .class = INFILTRATOR, .health = 600, .shields = 600 } }, { "Liara T'Soni", { .class = ADEPT, .health = 200, .shields = 800 } }, }]) / sizeof(*((struct { char* k; struct squadmate v; } []) { { "Jane Shepard", { .class = SOLDIER, .health = 800, .shields = 400 } }, { "Garrus Vakarian", { .class = INFILTRATOR, .health = 600, .shields = 600 } }, { "Liara T'Soni", { .class = ADEPT, .health = 200, .shields = 800 } }, }])))]) { 0 }, (struct squadmate [(sizeof((struct { char* k; struct squadmate v; } []) { { "Jane Shepard", { .class = SOLDIER, .health = 800, .shields = 400 } }, { "Garrus Vakarian", { .class = INFILTRATOR, .health = 600, .shields = 600 } }, { "Liara T'Soni", { .class = ADEPT, .health = 200, .shields = 800 } }, }]) / sizeof(*((struct { char* k; struct squadmate v; } []) { { "Jane Shepard", { .class = SOLDIER, .health = 800, .shields = 400 } }, { "Garrus Vakarian", { .class = INFILTRATOR, .health = 600, .shields = 600 } }, { "Liara T'Soni", { .class = ADEPT, .health = 200, .shields = 800 } }, }])))]) { 0 }, (unsigned long int [(sizeof((struct { char* k; struct squadmate v; } []) { { "Jane Shepard", { .class = SOLDIER, .health = 800, .shields = 400 } }, { "Garrus Vakarian", { .class = INFILTRATOR, .health = 600, .shields = 600 } }, { "Liara T'Soni", { .class = ADEPT, .health = 200, .shields = 800 } }, }]) / sizeof(*((struct { char* k; struct squadmate v; } []) { { "Jane Shepard", { .class = SOLDIER, .health = 800, .shields = 400 } }, { "Garrus Vakarian", { .class = INFILTRATOR, .health = 600, .shields = 600 } }, { "Liara T'Soni", { .class = ADEPT, .health = 200, .shields = 800 } }, }])))]) { 0 }, (struct { char* k; struct squadmate v; } []) { { "Jane Shepard", { .class = SOLDIER, .health = 800, .shields = 400 } }, { "Garrus Vakarian", { .class = INFILTRATOR, .health = 600, .shields = 600 } }, { "Liara T'Soni", { .class = ADEPT, .health = 200, .shields = 800 } }, });

  return 0;
}
