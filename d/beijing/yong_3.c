#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���ڶ���");
	set("long", @LONG
���ڶ�����һ�������Ĵ�֣�Ҳ�Ǳ��������ҵĵضΡ�һ����������ʯ��
�����д�����������ͷ���졣�����Ǿ����������ķ����š�
LONG );
	set("exits", ([
		"west" : __DIR__"yong_2",
                "south" : __DIR__"zsh_bjdamen",
	]));

	set("outdoors", "beijing");
	setup();
	replace_program(ROOM);
}

