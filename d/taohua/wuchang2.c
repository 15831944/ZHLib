// wuchang2.c

inherit ROOM;

void create()
{
	set("short", "���г�");
	set("long", @LONG
�������һ�����ָɽׯ���еĳ������󲿷ֵ��һ��������书����
һ���ĸ����Ժ����������ޣ������ϳ���ѧ��
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
