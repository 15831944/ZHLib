// File(/data/room/qiua/yishiting.c) of qiua's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "������");
	set ("long", @LONG
�������ʵ���˾�һ����Ҫ����������������֮���������в���
���Σ����������磬�����й�����������������ͨ���������� 
LONG );

	set("exits", ([
                "east"   : __DIR__"yanwu1",
                "west"   : __DIR__"yanwu2",
		"north"  : __DIR__"zhongting",
                "south"  : __DIR__"yingke",
	]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "��һ");
        set("room_name", "��ʵ");
        set("room_id", "qiua");
        set("room_owner_id", "qiua");
        set("room_position", "ɽ·");
}
