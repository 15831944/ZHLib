// Room: /city/kedian.c
// YZC 1995/12/04 

#include <room.h>

inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "�͵�");
	set("long", @LONG
����һ�Ҽ�Ǯ�����Ŀ�ջ������ǳ���¡������οͶ�ѡ��������ţ���
������������������صķ������顣��С����������æ������ת���Ӵ�����ǻ
�����Ŀ��ˡ��͵�����˴Ӳ�¶�棬��������˭���и��ָ����Ĳ²⡣ǽ�Ϲ�
��һ������(paizi)��
LONG );
	set("no_fight", 1);
	set("valid_startroom", 1);
        set("no_sleep_room",1);
	set("item_desc", ([
		"paizi" : "¥���ŷ���ÿҹʮ��������\n",
	]));
	set("objects", ([
		__DIR__"npc/xiaoer" : 1,
                __DIR__"npc/qi"     : 1,
	]));
	set("exits", ([
                "north" : HEIDIAN_DIR + "yangzhou_heidian",
		"east" : __DIR__"majiu",
                "pmc" : __DIR__"pmc",
		"west" : __DIR__"beidajie1",
		"up"   : __DIR__"kedian2",
	]));


	setup();
	"/clone/board/kedian_b"->foo();
        "/adm/npc/youxun"->come_here();
}

void init()
{
        add_all_action();
}

int valid_leave(object me, string dir)
{

	if (! me->query_temp("rent_paid") && dir == "up")
	        return notify_fail("��С��һ�µ���¥��ǰ������һ���������ţ����ס����\n");

	if (me->query_temp("rent_paid") && dir == "west")
	        return notify_fail("��С���ܵ��ű���ס���͹��Ѿ��������ӣ����᲻ס��������أ�
���˻���ΪС���ź����أ�\n");

	return ::valid_leave(me, dir);
}
