// wuchang2.c

inherit ROOM;

void create()
{
	set("short", "修行场");
	set("long", @LONG
这里是桃花岛弹指山庄修行的场所，大部分的桃花岛弟子武功有了
一定的根基以后就在这里苦修，领悟上乘武学。
LONG
	);
	set("exits", ([
		"east" : __DIR__"wuchang3",
	]));

 	set("objects", ([
		"/clone/npc/mu-ren" : 4,
                __DIR__"obj/bagua" : 1,
	]));

	set("outdoors", "taohua");
	setup();
	replace_program(ROOM);
}
