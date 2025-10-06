#include "set_pos.h"

spec( set_pos ) {
  argument(set<char*>* set);
  argument(char* element);

  precondition("a valid set");
    #define preconditions \
      set = allocator_push(spec_allocator, sizeof(*set)); \
      *set = set_alloc(char*, 16, spec_allocator);

  when("the element is present in the set") {
    #define element_is_present_condition \
      element = "a"; \
      set->data[11] = element; \
      set->hashes[11] = sim.hash_result;

    when("the element hash points to a free position") {
      apply(preconditions);
      apply(element_is_present_condition);

      sim.hash_result = 7;
      set->hashes[7] = 0;
      unsigned int result = set_pos(set, element);

      must("return the free position");
        verify(result == 7);

      must("finish immediately the linear probing");
        verify(sim.probe_count == 0);

      success();
    }; end();

    when("the element hash points to an occupied position") {
      when("there is a free position before the element") {
        apply(preconditions);
        apply(element_is_present_condition);

        sim.hash_result = 7;
        set_occupy(set, 7);
        set_occupy(set, 8);
        set_occupy(set, 9);
        unsigned int result = set_pos(set, element);

        must("return the free position");
          verify(result == 10);

        must("do a linear probing until finding the free position");
          verify(sim.probe_count == 3);
          verify(sim.probe_indexes[0] == 7);
          verify(sim.probe_indexes[1] == 8);
          verify(sim.probe_indexes[2] == 9);

        success();
      }; end();

      when("there is not a free position before the element") {
        when("the element hash is after its position") {
          sim.hash_result = 13;

          apply(preconditions);
          apply(element_is_present_condition);

          set_occupy(set, 13);
          set_occupy(set, 14);
          set_occupy(set, 15);
          set_occupy(set, 0);
          set_occupy(set, 1);
          set_occupy(set, 2);
          set_occupy(set, 3);
          set_occupy(set, 4);
          set_occupy(set, 5);
          set_occupy(set, 6);
          set_occupy(set, 7);
          set_occupy(set, 8);
          set_occupy(set, 9);
          set_occupy(set, 10);
          unsigned int result = set_pos(set, element);

          must("return the element position");
            verify(result == 11);

          must("do a linear probing until finding the element position, wrapping "\
               "around the data when the probe reaches its end");
            verify(sim.probe_count == 15);
            verify(sim.probe_indexes[0] == 13);
            verify(sim.probe_indexes[1] == 14);
            verify(sim.probe_indexes[2] == 15);
            verify(sim.probe_indexes[3] == 0);
            verify(sim.probe_indexes[4] == 1);
            verify(sim.probe_indexes[5] == 2);
            verify(sim.probe_indexes[6] == 3);
            verify(sim.probe_indexes[7] == 4);
            verify(sim.probe_indexes[8] == 5);
            verify(sim.probe_indexes[9] == 6);
            verify(sim.probe_indexes[10] == 7);
            verify(sim.probe_indexes[11] == 8);
            verify(sim.probe_indexes[12] == 9);
            verify(sim.probe_indexes[13] == 10);
            verify(sim.probe_indexes[14] == 11);

          success();
        }; end();

        when("the element hash is before its hash") {
          sim.hash_result = 7;

          apply(preconditions);
          apply(element_is_present_condition);

          set_occupy(set, 7);
          set_occupy(set, 8);
          set_occupy(set, 9);
          set_occupy(set, 10);
          unsigned int result = set_pos(set, element);

          must("return the element position");
            verify(result == 11);

          must("do a linear probing until finding the element position");
            verify(sim.probe_count == 5);
            verify(sim.probe_indexes[0] == 7);
            verify(sim.probe_indexes[1] == 8);
            verify(sim.probe_indexes[2] == 9);
            verify(sim.probe_indexes[3] == 10);
            verify(sim.probe_indexes[4] == 11);

          success();
        }; end();
      }; end();
    }; end();
  } end();

  when("the element is not present in the set") {
    #define element_not_present_condition \
      element = "a";

    when("the element hash points to a free position") {
      apply(preconditions);
      apply(element_not_present_condition);

      sim.hash_result = 7;
      set->hashes[7] = 0;
      unsigned int result = set_pos(set, element);

      must("return the free position");
        verify(result == 7);

      must("finish immediately the linear probing");
        verify(sim.probe_count == 0);

      success();
    }; end();

    when("the element hash points to an occupied position") {
      when("there is a free position in the set") {
        apply(preconditions);
        apply(element_not_present_condition);

        sim.hash_result = 7;
        set_occupy(set, 7);
        set_occupy(set, 8);
        set_occupy(set, 9);
        unsigned int result = set_pos(set, element);

        must("return the free position");
          verify(result == 10);

        must("do a linear probing until finding the free position");
          verify(sim.probe_count == 3);
          verify(sim.probe_indexes[0] == 7);
          verify(sim.probe_indexes[1] == 8);
          verify(sim.probe_indexes[2] == 9);

        success();
      }; end();

      when("there is not a free position int the set") {
        sim.hash_result = 13;

        apply(preconditions);
        apply(element_not_present_condition);

        set_occupy(set, 13);
        set_occupy(set, 14);
        set_occupy(set, 15);
        set_occupy(set, 0);
        set_occupy(set, 1);
        set_occupy(set, 2);
        set_occupy(set, 3);
        set_occupy(set, 4);
        set_occupy(set, 5);
        set_occupy(set, 6);
        set_occupy(set, 7);
        set_occupy(set, 8);
        set_occupy(set, 9);
        set_occupy(set, 10);
        set_occupy(set, 11);
        set_occupy(set, 12);
        unsigned int result = set_pos(set, element);

        must("return -1");
          verify(result == (unsigned int) -1);

        must("do a linear probing until scanning the whole set, wrapping "\
             "around the data when the probe reaches its end");
          verify(sim.probe_count == set->capacity);
          verify(sim.probe_indexes[0] == 13);
          verify(sim.probe_indexes[1] == 14);
          verify(sim.probe_indexes[2] == 15);
          verify(sim.probe_indexes[3] == 0);
          verify(sim.probe_indexes[4] == 1);
          verify(sim.probe_indexes[5] == 2);
          verify(sim.probe_indexes[6] == 3);
          verify(sim.probe_indexes[7] == 4);
          verify(sim.probe_indexes[8] == 5);
          verify(sim.probe_indexes[9] == 6);
          verify(sim.probe_indexes[10] == 7);
          verify(sim.probe_indexes[11] == 8);
          verify(sim.probe_indexes[12] == 9);
          verify(sim.probe_indexes[13] == 10);
          verify(sim.probe_indexes[14] == 11);
          verify(sim.probe_indexes[15] == 12);

        success();
      }; end();
    }; end();
  } end();

  #undef preconditions
}
