#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�����鷿");
	set("long", @LONG
�����������鷿��ȴû��һ���顣���ֹ���������Ŀ��������ͭ������
���������ʣ����鱦ʯ��Ӧ�о��У�ֻҪӵ��һ�����͹����һ�����ˡ���
��ǽ����һ��������������һ���顣
LONG );

	set("exits", ([
		"east" : __DIR__"aofu_zoulang3",
	]));
	set("objects", ([
		__DIR__"npc/shizhe" : 1,
	]));
	setup();
}
