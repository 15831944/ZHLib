// migong lev3

#include <ansi.h>

inherit NPC;


void create()

{
    
   set_name(RED"毒尾蝎"NOR, ({ "xie"}));
      
          set("race", "野兽");
       set("long",
"一只红褐色，满身斑点的蝎子。\n");
              set("attitude", "aggressive");
                set("vendetta/authority",1);

set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite" }) );
	       set("max_qi",1000+random(800));
  set("max_jing",1000+random(800));
  set("max_sen",1000+random(800));
  set("max_mana",1000+random(800));
  
      set("dex",40);
     set("str" ,45);
       
    set("age", 5);

       set("shen_type", -1);

        set("intellgent",1);

	set("pursuer",1);

        set("combat_exp", 1000000);
                  
        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/defence",100);

   setup();

        

}

void init( )

{
	object ob;	
        remove_call_out("hunting");
	if( interactive(ob = this_player())  ) {
        call_out("hunting",1);
        }
	if(!environment()->query("no_fight") && random(10) < 5)
        call_out("hunting",1);
}

void hunting()
{
	int i;
        object *ob;
        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
        if( !ob[i]->is_character() || ob[i]==this_object() || !living(ob[i])) continue;
        if(ob[i]->query("vendetta/authority")) continue;
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }
}



int hit_ob(object me, object ob, int damage)
{
   if( random(damage) > (int)ob->query_temp("apply/armor")
	&&	(int)ob->query_condition("xiezi_poison") < 10 ) {
		ob->apply_condition("xiezi_poison", 20);
        tell_object(ob, HIG "你觉得被咬中的地方一阵奇痒！\n" NOR );
	}
}

