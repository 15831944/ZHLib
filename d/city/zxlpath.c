inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "����¥����");
	set("long", @LONG
��������¥���ã������������˿ͺ�����С������������
��������̶��ĺ����������������������������������ַǷ���
�������������ǰ�����Ž��ĸ��ո����֣�����ʳ��������
õ���������ϵ���ĵ����������ܽ������
LONG);
	set("exits", ([
		"east"   : __DIR__"meigui",
		"north"  : __DIR__"furong",
		"south"  : __DIR__"mudan",
		"west"   : __DIR__"zuixianlou2",
	]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
        set("no_fight", 1);
	set("no_clean_up", 0);
        set("coor/x",20);
	set("coor/y",19);
        set("coor/z",10);
	setup();
	//replace_program(ROOM);
}
