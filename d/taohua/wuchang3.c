// wuchang1.c

inherit ROOM;

void create()
{
	set("short", "���г�");
	set("long", @LONG
�������һ�����ָɽׯ���еĳ������󲿷ֵ��һ��������书����
һ���ĸ����Ժ����������ޣ������ϳ���ѧ��������������ͬ��
�ǣ��������ż����������ɵ����ˣ�����ȥ�ǳ��⺷��
LONG
	);
	set("exits", ([
                "east"  : __DIR__"wuchang1",
                "west"  : __DIR__"wuchang2",
		"north" : __DIR__"houyuan",
	]));

 	set("objects", ([
		"/clone/npc/tie-ren" : 3,
               __DIR__"obj/bagua" : 1,
	]));

	set("outdoors", "taohua");
	setup();
	replace_program(ROOM);
}

