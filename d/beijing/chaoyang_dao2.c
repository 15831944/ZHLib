#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����ڳ�������ĳ������ϣ���·��������������������֣���ʱ������
��������߷ɳ۶���������һ·���������߾��ǳ������ˣ����߲�Զ���Ƿ�
������������֣��������У�ʮ�����֡�
LONG );
       set("exits", ([
		"west" : __DIR__"chaoyang_dao1",
		"east" : __DIR__"chaoyangmen",
	]));
	set("objects", ([
                "/kungfu/class/hu/pingsi" : 1,
		__DIR__"npc/tiaofu" : 1,
	]));
	set("outdoors", "beijing");
	setup();
	replace_program(ROOM);
}

