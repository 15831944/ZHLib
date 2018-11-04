// Room: /d/taishan/.c
// Date: CSWORD 96/03/25
inherit JIETI;

inherit ROOM;

void create()
{
	set("short", "东天门");
	set("long", @LONG
这里是岱顶的东面出口。往东依次经过伏虎门峡口、鹰愁涧等，
便可下山。
LONG );
        set("no_fight",1);
	set("exits", ([
		"west" : __DIR__"tanhai",
	]));
	set("no_clean_up", 0);
	set("outdoors", "taishan");
	setup();
}
void init()
{
        add_action("do_jieti","jieti");
        add_action("do_decide","decide");
}

