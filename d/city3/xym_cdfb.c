#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "侠义盟前");
        set("long",@LONG
这里是侠义盟成都分部的大门前面，侠义盟的成都分部地理位
置极好，掩映在青山碧水之间。这是一幢别具风格的建筑，让人觉
得一股正气浩存于天地之间。          
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
                "west" :  __DIR__"eastroad3",
                "east" : __DIR__"xym_cddt",
        ])); 
        set("objects", ([   
             __DIR__"npc/xym-guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "east") 
        {
           if (! me->query_temp("good_xym2") && me->query("bang_good/name") != "侠义盟")
               return notify_fail("守卫一把拦住你，朗声喝道：我侠义盟怎由闲杂人等随便进出。\n"); 
           else
           {
              me->delete_temp("good_xym2");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

