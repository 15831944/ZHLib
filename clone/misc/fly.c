#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_fly","flyup");
}

void create()
{
       set_name("飞行包", ({ "fly bag", "flybag", "bag" }) );
       set_weight(10);
       if( clonep() )
               set_default_object(__FILE__);
       else {
               set("unit", "个");
               set("long", "这是一个给新手用的飞行包,你可以用flyup来快速飞行。\n");
               set("no_get", 1);
               set("no_put", 1);
               set("no_drop", 1);
 }
       setup();
}

int do_fly( )
{
  object ob, myenv, where;
  ob = this_player () ;
  if (ob->is_busy())
  return notify_fail("你现在正忙着呢。\n");
  if (ob->is_fighting() )
  return notify_fail("你无法在战斗中使用飞行包！\n");
      if(!ob->query("born"))
  return notify_fail("你还没出生飞个屁！\n"); 

  if (ob->query("age") < 16)
  {
        where = environment(ob);
        if((string)where->short()==HIR"第十八层地狱"NOR)
                return notify_fail("地狱里面不能使用飞行包！\n");
        if (file_name(where)[0..5] == "/d/pk/" || where->query("no_ride") 
             || file_name(where)[0..11] == "/d/zhuanshi/" )  
                return notify_fail("这里不能使用飞行包！\n");              
        
        message_vision(HIC"$N发动了飞行包,$N飞了起来。\n"NOR,ob);
        message_vision(HIC"$N飞啊飞,飞了很长时间终于飞到了高空......\n"NOR, ob);
        ob->add("jing",ob->quer("max_jing"));
        ob->add("qi",ob->quer("max_qi"));
        myenv = environment (ob) ;
        ob->move ("/clone/misc/tian");
        return 1;
  }
  else  
  message_vision("只有16岁以下，并在安全地带"HIR"<不准战斗的地方>"HIR"才能使用飞行包!!\n"NOR,ob);
  return 1;
}
void owner_is_killed() {

        write(HIY"只见眼前金光一闪...好象是.....\n"NOR);
        destruct(this_object());
}

