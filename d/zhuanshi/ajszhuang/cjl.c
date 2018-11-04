// by yuchang
inherit ROOM; 
#include <ansi.h> 
#include <room.h>

void create()
{ 
      set("short", "藏剑庐密道");
      set("long",
"这是通往傲剑山庄的藏剑庐的密道，里面光线十分暗淡，\n"
"地上也十分潮湿，给人一阵毛骨耸然的感觉。\n");
      set("exits",([
            "north" : __DIR__"cjl2",
            "south" : __DIR__"square",
      ]));     
      setup();
}

int valid_leave(object me, string dir)
{     
        object ob;
    
        if ( ! me->query_temp("reborn_start/ao1") 
            && dir == "north" )   
        {
           if ( objectp(present("ao cangtian", environment(me))) )
              return -1; 
           ob = new(__DIR__"npc/aocangtian");   
           ob->move(environment(me));
           tell_room(environment(me),
                     CYN "\n突然只见一条黑影不知从哪里蹿了出来，"
                     "原来是傲剑山庄左圣傲苍天。\n\n"NOR);          
           return -1;              
        }
       return 1;

}

