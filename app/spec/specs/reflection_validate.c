#include "reflection_validate.h"

spec( reflection_validate ) {
  argument(void* target = nullptr);
  argument(struct reflection* reflection);

  when("the reflection does not have a validator function") {
    reflection = &(struct reflection) { 0 };
    reflection_validate(target, reflection);

    must("not do any validation");
      verify(sim.validator_called == false);

    success();
  } end();

  when("the reflection has a validator function") {
    reflection = &(struct reflection) { .validator = example_validator };

    when("the validator function fails") {
      sim.fail = true;
      reflection_validate(target, reflection);

      must("execute the validator function");
        verify(sim.validator_called == true);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(cstr_equal(failure.message, "fail fast and hard"));

      success();
    } end();

    when("the validator function succeeds") {
      sim.fail = false;
      reflection_validate(target, reflection);

      must("execute the validator function");
        verify(sim.validator_called == true);

      must("not fail");
        verify(failure.occurred == false);

      success();
    } end();
  } end();
}
