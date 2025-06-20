test( list, user_defined_types ) {

  /* Creates a stack allocated list: the list can be modified but it cannot grow over
   * its original capacity -- `6` in this case. */
  list<struct squadmate> squad = list_init(struct squadmate, 6);

  given("the Mass Effect starting squad");
    struct squadmate kaidan = { s("Kaidan Alenko"), SENTINEL, 300, 400 };
    struct squadmate jenkins = { s("Richard L. Jenkins"), SOLDIER, 200, 300 };
    list_push(&squad, kaidan);
    list_push(&squad, jenkins);
    verify(squad.length == 2);


  when("the first mission on Eden Prime is completed");
    list_pop(&squad); // Damned Geth: he will be avenged!
    struct squadmate ashley = { s("Ashley Williams"), SOLDIER, 400, 700 };
    list_push(&squad, ashley);
    verify(squad.length == 2);


  when("finding evidence on the Citadel");
    struct squadmate garrus = { s("Garrus Vakarian"), INFILTRATOR, 300, 500 };
    struct squadmate tali = { s("Tali Zorah"), ENGINEER, 200, 400 };
    struct squadmate wrex = { s("Urdnot Wrex"), VANGUARD, 800, 800 };
    list_push(&squad, garrus);
    list_push(&squad, tali);
    list_push(&squad, wrex);
    verify(squad.length == 5);


  when("rescuing Benezia's daughter on Therum");
    struct squadmate liara = { s("Liara T'Soni"), ADEPT, 100, 600 };
    list_push(&squad, liara);
    verify(squad.length == 6);


  must("be ready for the confrontation with the Thorian on Feros!");
    verify(squad.length == 6);


  success();
}
