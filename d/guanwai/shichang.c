// /guanwai/shichang.c

inherit ROOM;

void create()
{
	set("short", "��ʯ��");
	set("long", @LONG
������ɽ�ţ���ǰ��Ȼ������һ����ɽ������һ���Ѿ���ը��֧��
���飬�����ǿ���������������ʯ�ϡ��ڱ���Ҳ����ô���ʯɽ���㲻
����Щ���ȡ���ǰ��һ���ˣ�����������๤��
LONG );
	set("exits", ([
		"west" : __DIR__"tulu",
	]));

        set("objects", ([
                __DIR__"npc/jiangong" : 1,
        ]));

        set("no_fight", 1);

	set("outdoors", "guanwai");
	setup();
	replace_program(ROOM);
}

