#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
�������Ͻ��Ǳ��߿������ŵ�һ�������Ĵ�����Ϸ���Զ���Ǿ��ǵ�����
���ˣ���ʵ��̵Ĺų�ǽ�߸������š�ÿ�춼�������˾�������������뾩�ǡ�
�����򾭹���̳ͨ�����ǵ����ġ����������޼���ı����ֶ档
LONG );
	set("exits", ([
//                "west" : HEIDIAN_DIR + "beijing_heidian",
		"north" : __DIR__"tiantan",
		"south" : __DIR__"yongdingmen",
        "east" : __DIR__"wjb_bjwfb",
	]));
	set("objects", ([
		__DIR__"npc/tiaofu" : 1,
		__DIR__"npc/kid1" : 1,
		__DIR__"npc/tangzi" : 1,
	]));
	set("outdoors", "beijing");
	setup();
	replace_program(ROOM);
}
