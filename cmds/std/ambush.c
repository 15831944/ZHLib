// ambush.c  配合长安府狩猎任务的指令
#include <ansi.h>
#define QUARRY_OBJ   "/clone/quarry/"             //猎物的路径
 
inherit F_CLEAN_UP;

int main(object me)
{
        object ob;      

        if ( me->query("changanjob/kind") != "hunt" )        
        return notify_fail("你现在没有领取剿杀野兽的任务，不能埋伏！\n");         

        if ( me->query("changanjob/ok") )        
        return notify_fail("你现在已经完成本次狩猎任务了，快回去复命吧！\n");       
        
if ( me->query("combat_exp") > 3000000 )
return notify_fail("你的江湖经验已经很高了。\n");
        if ( environment(me)->query("no_fight") )
        return notify_fail("这里不是战斗场所不能埋伏！\n");     

        if ( me->is_busy() || me->query("doing") )
        return notify_fail("你现在正忙着呢！\n");  
 
        if ( me->is_fighting() )
        return notify_fail("你现在正打架呢，怎么能埋伏！\n"); 

        if (me->query("qi") < 30 )
        return notify_fail("你现在体力太差，不能埋伏！\n"); 

        if (me->query("jing") < 30 )
        return notify_fail("你现在精神太差，不能埋伏！\n"); 
     
        message_vision(HIC"$N找到一个僻静的角落，埋伏了起来。\n"NOR, me);        
        me->set_short_desc("正埋伏在此地。");
        me->delete_temp("pending/ambush");  
              
        me->start_busy((:call_other, __FILE__, "ambush" :), 
                      (:call_other, __FILE__, "halt_ambush" :)); 
        return 1;
}

int ambush(object me)
{
      object env;
      
      env = environment(me);

      if (me->add_temp("pending/ambush", 1) > 10 )
      {
          tell_object(me, HIY "你埋伏了半天，还是没有野兽出现，只得暂时放弃。\n" NOR);
          message("vision", HIY + me->name() + HIY "放松了精神，看来暂时不再继续埋伏了。\n" 
                   NOR, env, ({ me }));
          me->set_short_desc(0);
          me->delete_temp("pending/ambush"); 
          return 0;
       } 

        if (me->query("qi") < 20 ||
            me->query("jing") < 20)
        {
                tell_object(me, HIY "你实在太疲倦了，不能再继续埋伏，只好先休息一下。\n" NOR);
                message("vision", HIC + me->name() + HIC "一脸倦容，开始放松休息。\n" NOR,
                        env, ({ me }));
                me->set_short_desc(0);
                me->delete_temp("pending/ambush"); 
                return 0;
        }
        me->receive_damage("qi", 5);
        me->receive_damage("jing", 5);


       if ( me->query("changanjob/kind") == "hunt" &&
            me->query("changanjob/place") == env->short() &&
            me->query_temp("pending/ambush") > 5 &&
            random(5) == 1 )
       {
          call_other(__FILE__, "set_beast", me);       
          me->set_short_desc(0);
          me->delete_temp("pending/ambush"); 
          return 0;
        }
       return 1;
}

int halt_ambush(object me)
{            
	 message_vision(HIG"$N舒展了一下手脚，不再继续埋伏了。\n"NOR, me);        
        me->set_short_desc(0);  
        me->delete_temp("pending/ambush");     
        return 1;
}

void set_beast(object me)
{         
          string *list;
          object beast;
          int exp;
          exp = me->query("combat_exp");
          if (exp < 100000) exp = 100000;

          list = get_dir(QUARRY_OBJ);
          beast = new(QUARRY_OBJ + list[random(sizeof(list))]); 
          if ( ! beast || beast == 0) call_other(__FILE__, "set_beast", me); 
/*
          else
          { 
             if ( exp / 10000 - beast->query("power") <= 30
                  || exp / 10000 - beast->query("power") >= 50 )
                 call_other(__FILE__, "set_beast", me);  
*/
             else
             {
          	   beast->set("owner", me->query("id") );
          	   beast->set("no_auto_kill", 1);
          	   beast->move(environment(me));              
         	   message_vision(HIR"突然不知道从哪里蹿出来一只"NOR "$N" NOR 
                               HIR"。\n$n腾地一声就扑了上去。\n" NOR, beast, me);
                 me->kill_ob(beast);
                 beast->kill_ob(me);
          }
}

int help(object me)
{
        write(@HELP
这个指令可以用来埋伏等待野兽出现将其剿灭。
HELP );
        return 1;
}

