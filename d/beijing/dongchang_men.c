inherit ROOM;
#include <ansi.h>

void create()
{
	set("short",RED "��������");
	set("long", @LONG
������Ǿ��ǵ�����������������Ĵ��š����ﾯ�����ϣ���ʱ�д�����
���Ķ����ٱ���������������������ȥ�����������������������̫�ࡣ����
���ԵĶ����ٱ��������ƻ��Ķ����㿴������㲻�������Ļ�����û��ǸϿ�
�뿪�ĺá�
LONG NOR);
	set("exits", ([
		"south" : __DIR__"dongchang",
		"north" : __DIR__"dong_1",
	]));
	set("objects", ([
		__DIR__"npc/bing2" : 2,
		__DIR__"npc/taijian" : 1,
	]));
	set("no_fight", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	if (objectp(present("guan bing", environment(me))) && dir == "south")
		return notify_fail("�����ٱ����ֽ�����ס��\n\n");
	return ::valid_leave(me, dir);
}
