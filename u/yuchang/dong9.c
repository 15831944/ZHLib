// Room: /u/yuchang/dong1.c
// BY Yuchang

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
	set("short", HIR "麒麟窟" NOR);
        set("long", HIR "\n\n" 
"这是麒麟窟。进来顿觉一股热浪扑面而来，冲得你差点晕了\n"
"过去。四周一片通红，地面上冒着丝丝白气，脚底剧烈的炙痛\n"
"使你几乎立脚不住。热风带着隆隆巨响冲击着耳鼓，令你觉得\n"
"置身洪炉之中，全身的水分都在被一滴滴地烤干。你感到生命\n" 
"正离你而去·！\n\n" NOR 
     ); 
        set("exits", ([
                "east"      : __DIR__"dong1",
                "south"     : __DIR__"dong2",
                "west"      : __DIR__"dong1",
                "north"     : __DIR__"dong1",
	]));
        set("no_clean_up", 0);
        set("no_drop", 1);
     set("no_rideto",1); 
	setup();
}

void init()
{
        this_player()->set_temp("die_reason", "闯入麒麟窟，被烈炎烧死了");
        this_player()->receive_damage("qi", 2000);
        this_player()->receive_wound("qi",  2000);
        message_vision(HIR "突然四周燃起熊熊烈火，烈炎袭向$N！\n" NOR, this_player());
}

int valid_leave(object me, string dir)
{
	int count;

	if (member_array(dir, dirs) != -1)
	{
		if (dir == "west")
		{
//			write("*火克金*\n");
                        me->move("/d/zhuanshi/qilindong");
                        return notify_fail("恭喜你，你终于走出了迷宫。\n");
		}
	}
	return ::valid_leave(me, dir);
}

