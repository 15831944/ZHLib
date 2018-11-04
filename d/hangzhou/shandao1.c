// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "山道");
	set("long", @LONG
你正漫步在一条蜿蜒的山道上，两边繁茂的树木散发出淡淡的宜人的气息，溪
流在沟谷中流淌，水声潺潺如幻。花香满径，山光树色，绿影葱茏，辉映成画。
LONG );
	set("exits", ([
		"north" : __DIR__"shandao2",
		"west" : __DIR__"wenxin-quan",
		"south" : __DIR__"quanbian-xiaojing",
	]));
	
//	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
