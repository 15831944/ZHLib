inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","���ι�����Ժ");
	set("long", @LONG
���ǽ��ź��һ������Ļ�԰��������һ���᷿��������һ��������ͨ��
���ι����Ļ����������Ǻ��ι����Ĵ��ţ�������Ǵ����ˡ�
LONG );
	set("exits", ([
		"north" : __DIR__"hai_men",
		"south" : __DIR__"hai_dating",
		"east" : __DIR__"hai_huating",
		"west" : __DIR__"hai_fang",
	]));
	set("objects", ([
		__DIR__"npc/yuqian1" : 1,
		__DIR__"npc/yuqian2" : 1,
	]));

	setup();
}