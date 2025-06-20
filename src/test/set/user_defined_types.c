test( set, user_defined_types ) {

  /* Creates a stack allocated set: the set can be modified but it cannot grow over
   * its original capacity -- `6` in this case. */
  set<struct squadmate> squad = set_init(struct squadmate, 6);

  given("the Mass Effect starting squad");
    struct squadmate kaidan = { s("Kaidan Alenko"), SENTINEL, 300, 400 };
    struct squadmate jenkins = { s("Richard L. Jenkins"), SOLDIER, 200, 300 };
    set_add(&squad, kaidan);
    set_add(&squad, jenkins);
    verify(squad.length == 2);


  when("the first mission on Eden Prime is completed");
    set_del(&squad, jenkins); // Damned Geth: he will be avenged!
    struct squadmate ashley = { s("Ashley Williams"), SOLDIER, 400, 700 };
    set_add(&squad, ashley);
    verify(squad.length == 2);


  when("finding evidence on the Citadel");
    struct squadmate garrus = { s("Garrus Vakarian"), INFILTRATOR, 300, 500 };
    struct squadmate tali = { s("Tali Zorah"), ENGINEER, 200, 400 };
    struct squadmate wrex = { s("Urdnot Wrex"), VANGUARD, 800, 800 };
    set_add(&squad, garrus);
    set_add(&squad, tali);
    set_add(&squad, wrex);
    verify(squad.length == 5);


  when("rescuing Benezia's daughter on Therum");
    struct squadmate liara = { s("Liara T'Soni"), ADEPT, 100, 600 };
    set_add(&squad, liara);
    verify(squad.length == 6);


  when("detonating the bomb on Virmire");
    set_del(&squad, kaidan); // :'-(


  must("be ready for the final confrontation with Saren!");
    verify(squad.length == 5);


  success();
}
